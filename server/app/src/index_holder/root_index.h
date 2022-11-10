#pragma once

#include "app/src/index_holder/filenames_storage.h"

#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/home/qi/string/tst_map.hpp>

#include <filesystem>
#include <unordered_set>

class task_dispatcher;

class root_index
{
public:
  static root_index create(task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string);

  root_index(root_index&& other) noexcept;

  [[nodiscard]] std::size_t get_number_of_files() const noexcept;

  [[nodiscard]] bool is_equivalent(const std::filesystem::path& root) const;

  [[nodiscard]] const std::string& get_original_root() const;

  [[nodiscard]] std::vector<std::string> get_filenames(const std::string& word) const;

private:
  template<typename Char, typename T>
  using boost_symbols = boost::spirit::qi::symbols<Char, T, boost::spirit::qi::tst_map<Char, T>>;
  using symbols = boost_symbols<char, std::set<const filenames_storage::filename*>>;

  class creator;
  root_index(creator&& creator_);

  filenames_storage m_files;
  symbols m_symbols;

  std::filesystem::path m_root;
  std::string m_original_root;
};
