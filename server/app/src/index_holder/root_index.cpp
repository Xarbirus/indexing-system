#include "app/src/index_holder/root_index.h"

#include "app/src/misc/spinlock.h"
#include "app/src/task_dispatcher/task_dispatcher.h"

#include <fstream>

root_index::root_index(task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string)
  : m_root{root}
  , m_original_root{root_string}
{
  for(const auto& status : process_directory(m_root, dispatcher))
    status.wait();
}

root_index::root_index(const std::filesystem::path& root, const std::string& root_string)
  : m_root{root}
  , m_original_root{root_string}
{
  for(const auto& dir_entry : std::filesystem::recursive_directory_iterator(m_root))
    if(is_regular_file(dir_entry) and dir_entry.path().has_extension())
      add_file(dir_entry);
}

root_index::root_index(root_index&& other) noexcept
{
  std::scoped_lock lock{other.m_files_mutex, other.m_symbols_mutex};

  m_files = std::move(other.m_files);
  m_symbols = std::move(other.m_symbols);
  m_root = std::move(other.m_root);
  m_original_root = std::move(other.m_original_root);
}

std::list<std::future<void>> root_index::process_directory(const std::filesystem::path& path, task_dispatcher& dispatcher)
{
  spinlock spin;
  std::list<std::future<void>> statuses;
  process_directory_impl(path, dispatcher, statuses, spin);
  return statuses;
}

void root_index::process_directory_impl(const std::filesystem::path& path,
                                        task_dispatcher& dispatcher,
                                        std::list<std::future<void>>& statuses,
                                        spinlock& spin)
{
  for(const auto& dir_entry : std::filesystem::directory_iterator(path))
  {
    if(is_directory(dir_entry) and !is_empty(dir_entry))
    {
      auto status = dispatcher.add_task([&, dir_entry]() { process_directory_impl(dir_entry, dispatcher, statuses, spin); });
      std::scoped_lock lock{spin};
      statuses.emplace_back(std::move(status));
    }
    else if(is_regular_file(dir_entry) and dir_entry.path().has_extension())
      add_file(dir_entry);
  }
}

void root_index::add_file(const std::filesystem::path& path)
{
  auto get_file_number = [&, number = std::optional<size_t>()]() mutable
  {
    auto create_file_number = [&]()
    {
      auto relative_path = get_relative_path(path);
      std::unique_lock lock{m_files_mutex};
      m_files.emplace_back(relative_path.c_str());

      return m_files.size() - 1;
    };
    if(!number) [[unlikely]]
      number = create_file_number();
    return *number;
  };

  const auto locale = std::locale();
  const auto is_alnum = [&](wchar_t c) { return std::isalnum(c, locale); };
  const auto is_not_alnum = [&](wchar_t c) { return !std::isalnum(c, locale); };

  const auto file = read_file(path);
  auto word = std::find_if(file.cbegin(), file.cend(), is_alnum);
  while(word != file.cend())
  {
    auto delim = std::find_if(word, file.cend(), is_not_alnum);
    const auto file_number = get_file_number();

    std::unique_lock lock{m_symbols_mutex};
    if(auto found = m_symbols.find(std::wstring_view{word, delim}))
      found->insert(file_number);
    else
      m_symbols.add(word, delim, {file_number});
    lock.unlock();

    word = std::find_if(delim, file.cend(), is_alnum);
  }
}

std::wstring root_index::read_file(const std::filesystem::path& path)
{
  std::wfstream file{path};
  file.seekg(0, std::ios::end);
  auto len = file.tellg();
  if(len == -1) [[unlikely]]
    return {};
  file.seekg(0, std::ios::beg);

  std::wstring out;
  out.resize(static_cast<std::size_t>(len));
  file.read(out.data(), len);
  return out;
}

std::filesystem::path root_index::get_relative_path(const std::filesystem::path& path) const
{
  return relative(path, m_root);
}

size_t root_index::get_number_of_files() const noexcept
{
  return m_files.size();
}

bool root_index::is_equivalent(const std::filesystem::path& root) const
{
  return equivalent(root, m_root);
}
