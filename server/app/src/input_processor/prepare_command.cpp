#include "app/src/input_processor/prepare_command.h"

#include "app/src/input_processor/string_processing.h"

#include <boost/algorithm/string.hpp>

std::vector<std::string> prepare_command(std::string str)
{
  boost::to_lower(str);
  std::string_view processed{str};

  trim(processed);

  std::vector<std::string> args;
  boost::split(args, processed, boost::is_any_of(whitespaces), boost::token_compress_on);

  return args;
}