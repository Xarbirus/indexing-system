#include "app/src/input_processor/prepare_command.h"

#include <boost/algorithm/string.hpp>

std::pair<std::string, std::string> prepare_command(std::string str)
{
  constexpr auto whitespaces = " \t\n\r\v\f";

  boost::to_lower(str);
  boost::trim(str);

  const auto end = str.find_first_of(whitespaces);
  const auto suffix = str.find_first_not_of(whitespaces, end);

  return {str.substr(0, end), str.substr(suffix == std::string_view::npos ? str.size() : suffix)};
}