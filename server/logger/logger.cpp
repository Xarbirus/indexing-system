#include "logger/logger.h"

#include <spdlog/sinks/rotating_file_sink.h>

namespace logger
{
  void reset(const char* path, std::size_t log_size, std::size_t rotate_count)
  {
    spdlog::set_default_logger(spdlog::rotating_logger_mt("default", path, log_size, rotate_count));
    auto logger = spdlog::default_logger();
    logger->set_level( spdlog::level::level_enum::err);
    logger->flush_on(spdlog::level::level_enum::debug);
  }
}