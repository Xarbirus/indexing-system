#pragma once

#include "app/src/index_holder/file_info.h"
#include "app/src/index_holder/filenames_storage.h"

#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4459)
#endif
#include <boost/spirit/include/qi_symbols.hpp>
#include <boost/spirit/home/qi/string/tst_map.hpp>
#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning(pop)
#endif

#include <filesystem>
#include <map>
#include <unordered_set>

class task_dispatcher;

class root_index
{
public:
  static root_index create(std::atomic_bool& stop_flag, task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string);

  [[nodiscard]] std::size_t get_number_of_files() const noexcept;

  [[nodiscard]] bool is_equivalent(const std::filesystem::path& root) const;

  [[nodiscard]] const std::string& get_original_root() const;

  [[nodiscard]] std::vector<file_info> get_files_info(const std::string& word) const;

private:
  template<typename Char, typename T>
  using boost_symbols = boost::spirit::qi::symbols<Char, T, boost::spirit::qi::tst_map<Char, T>>;
  using symbol_files = std::map<const filenames_storage::filename*, std::size_t>;
  using symbols = boost_symbols<char, symbol_files>;

  class creator;
  root_index(creator&& creator_);

  filenames_storage m_files;
  symbols m_symbols;

  std::filesystem::path m_root;
  std::string m_original_root;
};
