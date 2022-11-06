#include "app/src/index_holder/root_index.h"

root_index::root_index(const std::filesystem::path& root, const std::string& root_string)
  : m_root{root}, m_original_root{root_string}
{}

bool root_index::is_equivalent(const std::filesystem::path& root) const
{
  return equivalent(m_root, root);
}