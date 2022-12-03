#include "app/src/input_processor/commands_holder.h"

#include "app/src/input_processor/command_processor/clear_processor.h"
#include "app/src/input_processor/command_processor/help_processor.h"
#include "app/src/input_processor/command_processor/index_processor.h"
#include "app/src/input_processor/command_processor/quit_processor.h"
#include "app/src/input_processor/command_processor/remove_processor.h"
#include "app/src/input_processor/command_processor/roots_processor.h"

commands_holder::commands_holder(engine& engine)
{
  add<clear_processor>("clear", engine);
  add<help_processor>("help", m_commands);
  add<index_processor>("index", engine);
  add<quit_processor>("quit", engine);
  add<remove_processor>("remove", engine);
  add<roots_processor>("roots", engine);
}

void commands_holder::execute(const std::string& command, std::string_view arguments)
{
  if(auto it = m_commands.find(command); it != m_commands.end())
    it->second->execute(arguments);
  else
    m_commands.at("help")->execute(arguments);
}
