#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

#include <map>
#include <memory>

class engine;

class commands_holder
{
public:
  explicit commands_holder(engine& engine);

  void execute(const std::string& command, const std::string& arguments);

private:
  std::map<std::string, std::unique_ptr<command_processor>> m_commands;
};
