#include "app/src/input_processor/command_processor/help_processor.h"

#include "app/src/input_processor/prepare_command.h"
#include "app/src/misc/print_to_user.h"

help_processor::help_processor(std::string _command, const std::map<std::string, std::unique_ptr<command_processor>>& commands)
  : command_info{std::move(_command), "Use '{0}' to see a list of commands. Use '{0} <command>' to see information about a specific command."}
  , m_commands{commands}
{}

void help_processor::execute(std::string_view arguments)
{
  const auto [command_to_help, _] = separate_first_word(arguments);
  if(auto it = m_commands.get().find(command_to_help); it != m_commands.get().end())
    print_to_user(it->second->get_description());
  else
  {
    print_to_user("Available commands:");
    for(const auto& _command : m_commands.get())
      print_to_user('\t', _command.first, '\t', _command.second->get_description());
  };
}

std::string_view help_processor::get_description() const noexcept
{
  return description;
}
