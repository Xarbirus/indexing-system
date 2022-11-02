#include "logger/src/details/format_pattern.h"

#include <spdlog/details/fmt_helper.h>

namespace logger::details
{
  void format_pattern::apply(spdlog::logger& logger)
  {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<format_pattern>('*').set_pattern("%Y.%m.%d %H:%M:%S.%e [%t] %-7l:%* %v");
    logger.set_formatter(std::move(formatter));
  }

  std::unique_ptr<spdlog::custom_flag_formatter> format_pattern::clone() const
  {
    return std::make_unique<format_pattern>();
  }

  void format_pattern::format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest)
  {
    if(!msg.source.funcname || !msg.source.filename)
      return;

    dest.push_back(' ');
    dest.push_back('[');
    dest.append(get_short_filename(msg.source.filename));
    dest.push_back(':');
    spdlog::details::fmt_helper::append_int(msg.source.line, dest);
    dest.push_back(':');
    dest.append(get_pretty_function_name(msg.source.funcname));
    dest.push_back(']');
  }

  std::string_view format_pattern::get_short_filename(std::string_view filename)
  {
#ifdef _WIN32
    const auto it = std::find_first_of(filename.rbegin(), filename.rend(), std::begin(spdlog::details::os::folder_seps), std::end(spdlog::details::os::folder_seps) - 1);
    return it != filename.rend() ? it.base() : filename;
#else
    auto rv = std::strrchr(filename.data(), spdlog::details::os::folder_seps[0]);
    return rv != nullptr ? rv + 1 : filename;
#endif
  }

  std::string_view format_pattern::get_pretty_function_name(std::string_view pretty_name)
  {
    if(pretty_name.rfind("<lambda") != std::string::npos)
      return "lambda";

    //skip "()" inside templated args
    auto angle = pretty_name.find('<');
    auto round = pretty_name.find('(');
    while(angle < round)
    {
      auto end = pretty_name.find('>', angle) + 1;
      angle = pretty_name.find('<', end);
      round = pretty_name.find('(', end);
    }
    pretty_name.remove_suffix(pretty_name.size() - round);  //cut args
    pretty_name.remove_prefix(pretty_name.rfind(' ') + 1);  //cut return type
    auto begin = pretty_name.rfind("::", pretty_name.rfind("::") - 1);  //cut extra namespaces
    return begin == std::string::npos ? pretty_name : pretty_name.substr(begin + 2);
  }
}