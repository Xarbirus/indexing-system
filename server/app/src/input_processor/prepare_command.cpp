#include "app/src/input_processor/prepare_command.h"

#include <boost/algorithm/string.hpp>

std::pair<std::string, std::string> separate_first_word(std::string_view str)
{
  constexpr auto whitespaces = " \t\n\r\v\f";

  const auto end = str.find_first_of(whitespaces);
  const auto suffix = str.find_first_not_of(whitespaces, end);

  return std::pair<std::string, std::string>(str.substr(0, end), str.substr(suffix == std::string_view::npos ? str.size() : suffix));
}

std::pair<std::string, std::string> prepare_command(std::string str)
{
  boost::trim(str);

  auto out = separate_first_word(str);
  boost::to_lower(out.first);

  return out;
}