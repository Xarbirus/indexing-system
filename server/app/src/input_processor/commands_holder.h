#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

#include <map>
#include <memory>

class engine;

class commands_holder
{
public:
  explicit commands_holder(engine& engine);

  void execute(const std::string& command, std::string_view arguments);

private:
  template<typename Processor, typename... Args>
  void add(const std::string& command, Args&&... args)
  {
    m_commands.emplace(command, std::make_unique<Processor>(command, std::forward<Args>(args)...));
  }

  std::map<std::string, std::unique_ptr<command_processor>> m_commands;
};
