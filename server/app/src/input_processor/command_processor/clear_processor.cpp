#include "app/src/input_processor/command_processor/clear_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/remove_root_result.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

clear_processor::clear_processor(engine& engine)
  : m_engine{engine}
{}

void clear_processor::execute(const std::string&)
{
  const auto result = m_engine.clear_roots();
  const auto duration = to_user(result.duration);
  print_to_user(fmt::format("Finished in {}.", duration));
  LOG_INFO("Index was cleared ({}).", duration);
}

std::string clear_processor::get_description() const
{
  return description;
}
