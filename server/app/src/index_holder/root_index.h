#pragma once

#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/home/qi/string/tst_map.hpp>

#include <filesystem>
#include <shared_mutex>
#include <unordered_set>

class root_index
{
public:
  root_index(const std::filesystem::path& root, const std::string& root_string);
  root_index(root_index&& other) noexcept;

  root_index& operator=(root_index&& other) noexcept;

  size_t get_number_of_files() const noexcept;

  bool is_equivalent(const std::filesystem::path& root) const;

private:
  void add_file(const std::filesystem::path& path);
  std::wstring read_file(const std::filesystem::path& path) const;

  std::filesystem::path get_relative_path(const std::filesystem::path& path) const;

  template<typename Char, typename T>
  using root_symbols = boost::spirit::qi::symbols<Char, T, boost::spirit::qi::tst_map<Char, T>>;

  mutable std::shared_mutex m_files_mutex;
  mutable std::shared_mutex m_symbols_mutex;

  std::vector<std::string> m_files;
  root_symbols<wchar_t, std::unordered_set<size_t>> m_symbols;

  std::filesystem::path m_root;
  std::string m_original_root;
};
