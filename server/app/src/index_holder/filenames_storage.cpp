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

std::optional<std::filesystem::path> filenames_storage::get_file(const filename* file_indices) const
{
  if(!file_indices or file_indices->empty())
    return std::nullopt;

  std::filesystem::path out;
  for(part_index index : *file_indices)
  {
    auto iter = m_parts.right.find(index);
    if(iter == m_parts.right.end())
      return std::nullopt;
    out /= iter->second;
  }
  return out;
}
