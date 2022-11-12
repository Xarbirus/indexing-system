#include "app/src/input_processor/command_processor/command_info.h"

#include <fmt/format.h>

command_info::command_info(std::string _command, std::string_view description_template)
  : command{std::move(_command)}
  , description{fmt::vformat(description_template, fmt::make_format_args(command))}
{}