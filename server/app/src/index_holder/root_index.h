#pragma once

#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/home/qi/string/tst_map.hpp>

#include <filesystem>
#include <unordered_set>

class task_dispatcher;

template<typename Char, typename T>
using boost_symbols = boost::spirit::qi::symbols<Char, T, boost::spirit::qi::tst_map<Char, T>>;
using root_symbols = boost_symbols<wchar_t, std::unordered_set<size_t>>;

using root_files = std::vector<std::string>;

class root_index
{
public:
  static root_index create(task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string);

  root_index(root_index&& other) noexcept;

  [[nodiscard]] size_t get_number_of_files() const noexcept;

  [[nodiscard]] bool is_equivalent(const std::filesystem::path& root) const;

private:
  class creator;
  root_index(creator&& creator_);

  root_files m_files;
  root_symbols m_symbols;

  std::filesystem::path m_root;
  std::string m_original_root;
};
