#pragma once

#include <string>

struct command_info
{
  command_info(std::string _command, std::string_view description_template);

  std::string command;
  std::string description;
};
