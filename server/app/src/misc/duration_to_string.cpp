#include "app/src/misc/duration_to_string.h"

#include <fmt/chrono.h>

std::string to_user(const std::chrono::system_clock::duration& duration)
{
  return fmt::format("{:%M minute(s) %S second(s)}", floor<std::chrono::seconds>(duration));
}
