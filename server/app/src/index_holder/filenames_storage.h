#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <boost/bimap.hpp>

class filenames_storage
{
public:
  using part_index = std::size_t;
  using filename = std::vector<part_index>;

  [[nodiscard]] std::size_t size() const noexcept;

  const filename* add_file(const std::filesystem::path& file);

  [[nodiscard]] std::optional<std::filesystem::path> get_file(const filename* file_indices) const;

private:
  boost::bimap<std::string, part_index> m_parts;
  std::set<filename> m_files;
};
