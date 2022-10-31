#include "logger/logger.h"

#include <spdlog/sinks/rotating_file_sink.h>

namespace
{
  spdlog::level::level_enum to_spdlog_level(logger::levels level)
  {
    switch(level)
    {
      case logger::levels::off: return spdlog::level::level_enum::off;
      case logger::levels::normal: return spdlog::level::level_enum::info;
      case logger::levels::extended: return spdlog::level::level_enum::trace;
    }
    return spdlog::level::level_enum::trace;
  }
}

namespace logger
{
  void reset(const char* path, std::size_t log_size, std::size_t rotate_count, levels level)
  {
    spdlog::set_default_logger(spdlog::rotating_logger_mt("default", path, log_size, rotate_count));
    auto logger = spdlog::default_logger();
    logger->set_level(to_spdlog_level(level));
    logger->flush_on(spdlog::level::level_enum::debug);
  }
}