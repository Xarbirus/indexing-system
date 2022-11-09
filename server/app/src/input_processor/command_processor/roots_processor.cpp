#include "app/src/input_processor/command_processor/roots_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

roots_processor::roots_processor(engine& engine)
  : m_engine{engine}
{}

void roots_processor::execute(const std::string&)
{
  const auto result = m_engine.get_roots();
  const auto duration = to_user_string(result.duration);
  print_to_user(fmt::format("Finished in {}.", duration));
  LOG_INFO("Find {} roots ({}).", result.roots.size(), duration);
}

std::string roots_processor::get_description() const
{
  return description;
}
