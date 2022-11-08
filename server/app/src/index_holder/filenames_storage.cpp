#include "app/src/index_holder/filenames_storage.h"

std::size_t filenames_storage::size() const noexcept
{
  return m_files.size();
}

const filenames_storage::filename* filenames_storage::add_file(const std::filesystem::path& file)
{
  filename indices;
  for(const auto& word : file)
    indices.push_back(m_parts.insert({word.string(), m_parts.size()}).first->right);

  return &(*m_files.emplace(std::move(indices)).first);
}
