#include "app/src/misc/duration_to_string.h"

#include <fmt/chrono.h>

std::string to_user_string(const std::chrono::system_clock::duration& duration)
{
  return fmt::format("{} minute(s) {} second(s)",
                     floor<std::chrono::minutes>(duration).count(),
                     floor<std::chrono::seconds>(duration).count() % 60);
}
