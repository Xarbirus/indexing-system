#include "app/src/index_holder/root_index_creator.h"

#include "app/src/task_dispatcher/task_dispatcher.h"

#include <fstream>

root_index::creator::creator(task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string)
  : m_dispatcher{dispatcher}
  , m_root{root}
  , m_original_root{root_string}
{
  add_directory(m_root);
  for(const auto& status : m_statuses)
    status.wait();
}

std::wstring root_index::creator::read_file(const std::filesystem::path& path)
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

void root_index::creator::add_file(const std::filesystem::path& path)
{
  auto get_file_number = [&, number = std::optional<size_t>()]() mutable
  {
    auto create_file_number = [&]()
    {
      auto relative_path = relative(path, m_root);
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

void root_index::creator::add_directory(const std::filesystem::path& path)
{
  for(const auto& dir_entry : std::filesystem::directory_iterator(path))
  {
    if(is_directory(dir_entry) and !is_empty(dir_entry))
    {
      auto status = m_dispatcher.add_task([&, dir_entry]() { add_directory(dir_entry); });
      std::scoped_lock lock{m_spin};
      m_statuses.emplace_back(std::move(status));
    }
    else if(is_regular_file(dir_entry) and dir_entry.path().has_extension())
      add_file(dir_entry);
  }
}
