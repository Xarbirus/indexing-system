#pragma once

#include "logger/src/logger_levels.h"

#include <cstdlib>

namespace logger
{
  constexpr auto default_log_path = "server.log";
  constexpr std::size_t default_log_size = 1'024*1'024*10;
  constexpr std::size_t default_log_files = 10;
#ifdef NDEBUG
  constexpr levels default_log_level = levels::normal;
#else
  constexpr levels default_log_level = levels::extended;
#endif
}