#include "app/src/input_processor/command_processor/help_processor.h"

#include "app/src/input_processor/prepare_command.h"
#include "app/src/misc/print_to_user.h"

help_processor::help_processor(const std::map<std::string, std::unique_ptr<command_processor>>& commands)
  : m_commands{commands}
{}

void help_processor::execute(const std::string& arguments)
{
  const auto [command_to_help, _] = prepare_command(arguments);
  if(auto it = m_commands.find(command_to_help); it != m_commands.end())
    print_to_user(it->second->get_description());
  else
  {
    print_to_user("Available commands:");
    for(const auto& command : m_commands)
      print_to_user('\t', command.first, '\t', command.second->get_description());
  };
}

std::string help_processor::get_description() const
{
  return description;
}