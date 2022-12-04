#include "app/src/index_holder/root_index_creator.h"

#include "app/src/task_dispatcher/task_dispatcher.h"

#include <fstream>

root_index::creator::creator(std::atomic_bool& stop_flag, task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string)
  : m_stop_flag{stop_flag}
  , m_dispatcher{dispatcher}
  , m_root{root}
  , m_original_root{root_string}
  , m_current_locale{std::locale()}
{
  add_directory(m_root);
  for(const auto& status : m_statuses)
    status.wait();
}

std::string root_index::creator::read_file(const std::filesystem::path& path)
{
  std::fstream file{path};
  file.seekg(0, std::ios::end);
  auto len = file.tellg();
  if(len == -1) [[unlikely]]
    return {};
  file.seekg(0, std::ios::beg);

  std::string out;
  out.resize(static_cast<std::size_t>(len));
  file.read(out.data(), len);
  return out;
}

void root_index::creator::add_file(const std::filesystem::path& path)
{
  auto get_filename_indices = [&, current_indices = static_cast<const filenames_storage::filename*>(nullptr)]() mutable
  {
    if(current_indices == nullptr) [[unlikely]]
    {
      std::scoped_lock lock{m_files_mutex};
      current_indices = m_files.add_file(relative(path, m_root));
    }
    return current_indices;
  };

  const auto file = read_file(path);

  const auto is_not_alnum = [&](char c)
  {
    static constexpr auto* punct = R"STR(\|/.,:;?!"()[]{}*#$%&'+-<=>@№^`~)STR";
    return std::strchr(punct, c) != nullptr or std::isblank(c, m_current_locale) or std::isspace(c, m_current_locale);
  };
  const auto is_alnum = [&](char c) { return !is_not_alnum(c); };

  auto word = std::find_if(file.cbegin(), file.cend(), is_alnum);
  while(word != file.cend())
  {
    auto delim = std::find_if(word, file.cend(), is_not_alnum);
    std::unique_lock lock{m_symbols_mutex};
    if(auto found = m_symbols.find(std::string_view{word, delim}))
    {
      auto result = found->try_emplace(get_filename_indices(), 0);
      result.first->second++;
    }
    else
      m_symbols.add(word, delim, symbol_files{{get_filename_indices(), 1}});
    lock.unlock();

    word = std::find_if(delim, file.cend(), is_alnum);
  }
}

void root_index::creator::add_directory(const std::filesystem::path& path)
{
  for(const auto& dir_entry : std::filesystem::directory_iterator(path))
  {
    if(m_stop_flag.load(std::memory_order_acquire))
      break;

    if(is_directory(dir_entry) and !is_empty(dir_entry))
    {
      auto task = [&, dir_entry]() { add_directory(dir_entry); };
      auto status = m_dispatcher.add_task(std::move(task));
      std::scoped_lock lock{m_spin};
      m_statuses.emplace_back(std::move(status));
    }
    else if(is_regular_file(dir_entry) and dir_entry.path().has_extension())
      add_file(dir_entry);
  }
}
