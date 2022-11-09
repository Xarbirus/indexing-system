#include "check_host_address.h"

#include <regex>

bool is_correct_host_address(std::string_view address)
{
  static const std::regex address_template(
    "^(((([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))|localhost):"
    "((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-9]{1,4}))$",
    std::regex::icase);
  return std::regex_match(address.data(), address_template);
}
