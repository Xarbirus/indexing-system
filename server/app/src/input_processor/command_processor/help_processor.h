#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

#include <map>
#include <memory>

class help_processor : public command_processor
{
public:
  explicit help_processor(const std::map<std::string, std::unique_ptr<command_processor>>& commands);

  void execute(const std::string& arguments) override;

  [[nodiscard]] std::string get_description() const override;

private:
  const std::map<std::string, std::unique_ptr<command_processor>>& m_commands;

  static constexpr auto description =
    "Use 'help' to see a list of commands. "
    "Use 'help <command>' to see information about a specific command.";
};