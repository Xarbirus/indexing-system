#include "logger/gtests/details/check_message.h"
#include "logger/src/details/format_pattern.h"

#include <gtest/gtest.h>

void check(const spdlog::details::log_msg& message, std::string_view master_value)
{
  std::tm time{};
  spdlog::memory_buf_t buffer;
  logger::details::format_pattern().format(message, time, buffer);

  EXPECT_EQ(buffer.size(), master_value.size());

  for(std::size_t i = 0; i < buffer.size(); i++)
    EXPECT_EQ(buffer[i], master_value[i]);
}
