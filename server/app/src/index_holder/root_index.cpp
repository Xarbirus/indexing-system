#include "app/src/index_holder/root_index.h"

#include "app/src/index_holder/root_index_creator.h"

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

size_t root_index::get_number_of_files() const noexcept
{
  return m_files.size();
}

bool root_index::is_equivalent(const std::filesystem::path& root) const
{
  return equivalent(root, m_root);
}
