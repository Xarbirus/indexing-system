#include "app/src/input_processor/command_processor/clear_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/remove_root_result.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

clear_processor::clear_processor(engine& engine)
  : m_engine{engine}
{}

void clear_processor::execute(const std::string&)
{
  const auto result = m_engine.clear_roots();
  print_to_user(fmt::format("Finished in {} minute(s).", result.duration.count()));
  LOG_INFO("Index was cleared ({} minute(s)).", result.duration.count());
}

std::string clear_processor::get_description() const
{
  return description;
}
