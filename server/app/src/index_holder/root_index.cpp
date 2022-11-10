#include "app/src/index_holder/root_index.h"

#include "app/src/index_holder/root_index_creator.h"
#include "app/src/misc/spinlock.h"

#include "logger/src/logger.h"

#include <execution>

root_index root_index::create(task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string)
{
  return root_index::creator{dispatcher, root, root_string};
}

root_index::root_index(creator&& creator_)
  : m_files{std::move(creator_.m_files)}
  , m_symbols{std::move(creator_.m_symbols)}
  , m_root{std::move(creator_.m_root)}
  , m_original_root{std::move(creator_.m_original_root)}
{}

root_index::root_index(root_index&& other) noexcept
{
  m_files = std::move(other.m_files);
  m_symbols = std::move(other.m_symbols);
  m_root = std::move(other.m_root);
  m_original_root = std::move(other.m_original_root);
}

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

std::vector<std::string> root_index::get_filenames(const std::string& word) const
{
  std::vector<std::string> out;

  std::set<const filenames_storage::filename*> filenames;
  if(boost::spirit::qi::parse(word.begin(), word.end(), m_symbols, filenames))
  {
    LOG_DEBUG("Found {} files with word '{}' in root {}.", filenames.size(), word, m_original_root);

    spinlock spin;
    auto filler = [&](const filenames_storage::filename* indices) mutable
    {
      if(auto file = m_files.get_file(indices); file)
      {
        std::scoped_lock lock{spin};
        out.emplace_back(file->string());
      }
    };
    out.reserve(filenames.size());
    std::for_each(std::execution::par, filenames.begin(), filenames.end(), filler);
  }
  else
    LOG_DEBUG("Didn't find files with word '{}' in root {}.", word, m_original_root);

  return out;
}