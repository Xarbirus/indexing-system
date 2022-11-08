#include "app/src/input_processor/command_processor/roots_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/get_roots_result.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

roots_processor::roots_processor(engine& engine)
  : m_engine{engine}
{}

void roots_processor::execute(const std::string&)
{
  const auto result = m_engine.get_roots();
  print_to_user(fmt::format("Finished in {} minute(s).", result.duration.count()));
  LOG_INFO("Find {} roots ({} minute(s)).", result.roots.size(), result.duration.count());
}

std::string roots_processor::get_description() const
{
  return description;
}
