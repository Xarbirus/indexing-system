#include "app/src/input_processor/prepare_command.h"

#include <boost/algorithm/string.hpp>

std::vector<std::string> prepare_command(std::string str)
{
  static constexpr auto whitespaces = " \t\n\r\v\f";

  boost::to_lower(str);
  std::string_view trimmed{str};

  trimmed.remove_prefix(std::min(trimmed.find_first_not_of(whitespaces), trimmed.size()));
  if(auto suffix = trimmed.find_last_not_of(whitespaces); suffix != std::string::npos)
    trimmed.remove_suffix(trimmed.size() - suffix - 1);

  std::vector<std::string> args;
  boost::split(args, trimmed, boost::is_any_of(whitespaces), boost::token_compress_on);

  return args;
}