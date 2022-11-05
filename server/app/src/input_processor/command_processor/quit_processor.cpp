#include "app/src/input_processor/command_processor/quit_processor.h"

#include "app/src/engine/engine.h"

quit_processor::quit_processor(engine& engine)
  : m_engine{engine}
{}

void quit_processor::execute(const std::string&)
{
  m_engine.stop_service();
}

std::string quit_processor::get_description() const
{
  return description;
}
