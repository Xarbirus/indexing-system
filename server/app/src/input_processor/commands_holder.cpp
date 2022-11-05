#include "app/src/input_processor/commands_holder.h"

#include "app/src/input_processor/command_processor/help_processor.h"
#include "app/src/input_processor/command_processor/index_processor.h"
#include "app/src/input_processor/command_processor/quit_processor.h"
#include "app/src/input_processor/command_processor/remove_processor.h"

commands_holder::commands_holder(engine& engine)
{
  m_commands.emplace("help", std::make_unique<help_processor>(m_commands));
  m_commands.emplace("index", std::make_unique<index_processor>(engine));
  m_commands.emplace("quit", std::make_unique<quit_processor>(engine));
  m_commands.emplace("remove", std::make_unique<remove_processor>(engine));
}

void commands_holder::execute(const std::string& command, const std::string& arguments)
{
  if(auto it = m_commands.find(command); it != m_commands.end())
    it->second->execute(arguments);
  else
    m_commands.at("help")->execute(arguments);
}
