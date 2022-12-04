#include "app/src/index_holder/root_index.h"

#include "app/src/index_holder/root_index_creator.h"
#include "app/src/misc/spinlock.h"

#include "logger/src/logger.h"

#include <execution>

root_index root_index::create(std::atomic_bool& stop_flag, task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string)
{
  return root_index::creator{stop_flag, dispatcher, root, root_string};
}

root_index::root_index(creator&& creator_)
  : m_files{std::move(creator_.m_files)}
  , m_symbols{std::move(creator_.m_symbols)}
  , m_root{std::move(creator_.m_root)}
  , m_original_root{std::move(creator_.m_original_root)}
{}

std::size_t root_index::get_number_of_files() const noexcept
{
  return m_files.size();
}

bool root_index::is_equivalent(const std::filesystem::path& root) const
{
  return equivalent(root, m_root);
}

const std::string& root_index::get_original_root() const
{
  return m_original_root;
}

std::vector<file_info> root_index::get_files_info(const std::string& word) const
{
  std::vector<file_info> out;

  symbol_files files;
  if(boost::spirit::qi::parse(word.begin(), word.end(), m_symbols, files))
  {
    LOG_DEBUG("Found {} files with word '{}' in root {}.", files.size(), word, m_original_root);

    spinlock spin;
    auto filler = [&](const auto& info) mutable
    {
      if(auto file = m_files.get_file(info.first); file)
      {
        std::scoped_lock lock{spin};
        out.emplace_back(file->string(), info.second);
      }
    };
    out.reserve(files.size());
    std::for_each(std::execution::par, files.begin(), files.end(), filler);
  }
  else
    LOG_DEBUG("Didn't find files with word '{}' in root {}.", word, m_original_root);

  return out;
}