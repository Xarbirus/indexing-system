#include "app/src/input_processor/string_processing.h"

void trim(std::string_view& str)
{
  str.remove_prefix(std::min(str.find_first_not_of(whitespaces), str.size()));
  if(auto suffix = str.find_last_not_of(whitespaces); suffix != std::string_view::npos)
    str.remove_suffix(str.size() - suffix - 1);
}
