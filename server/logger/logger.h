#pragma once

#include "logger/logger_levels.h"

#include <spdlog/spdlog.h>

#define LOG_ERROR(msg, ...) \
  spdlog::log({__FILE__, __LINE__, __PRETTY_FUNCTION__}, spdlog::level::level_enum::err, msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) \
  spdlog::log({__FILE__, __LINE__, __PRETTY_FUNCTION__}, spdlog::level::level_enum::warn, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) \
  spdlog::log({__FILE__, __LINE__, __PRETTY_FUNCTION__}, spdlog::level::level_enum::info, msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) \
  spdlog::log({__FILE__, __LINE__, __PRETTY_FUNCTION__}, spdlog::level::level_enum::debug, msg, ##__VA_ARGS__)
#define LOG_TRACE spdlog::log({__FILE__, __LINE__, __PRETTY_FUNCTION__}, spdlog::level::level_enum::debug, "")

namespace logger
{
  void reset(const char* path, std::size_t log_size, std::size_t rotate_count, levels level);
}
