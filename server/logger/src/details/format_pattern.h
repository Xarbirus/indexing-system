#pragma once

#include <spdlog/logger.h>
#include <spdlog/pattern_formatter.h>

namespace logger::details
{
  class format_pattern : public spdlog::custom_flag_formatter
  {
  public:
    static void apply(spdlog::logger& logger);

    [[nodiscard]] std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;

    void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override;

  private:
    static std::string_view get_short_filename(std::string_view filename);
    static std::string_view get_pretty_function_name(std::string_view pretty_name);
  };
}
