#include "app/src/input_processor/command_processor/quit_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/misc/print_to_user.h"

quit_processor::quit_processor(std::string _command, engine& engine)
  : command_info{std::move(_command), "Use '{}' to stop the service."}
  , m_engine{engine}
{}

void quit_processor::execute(std::string_view arguments)
{
  if(!arguments.empty())
  {
    print_to_user("Extra argument!\n", description);
    return;
  }

  m_engine.stop_service();
}

std::string_view quit_processor::get_description() const
{
  return description;
}
