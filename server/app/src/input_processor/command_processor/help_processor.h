#pragma once

#include "app/src/input_processor/command_processor/command_info.h"
#include "app/src/input_processor/command_processor/command_processor.h"

#include <map>
#include <memory>

class help_processor : public command_processor, private command_info
{
public:
  help_processor(std::string _command, const std::map<std::string, std::unique_ptr<command_processor>>& commands);

  void execute(std::string_view arguments) override;

  [[nodiscard]] std::string_view get_description() const override;

private:
  const std::map<std::string, std::unique_ptr<command_processor>>& m_commands;

  static constexpr auto description =
    "Use 'help' to see a list of commands. "
    "Use 'help <command>' to see information about a specific command.";
};