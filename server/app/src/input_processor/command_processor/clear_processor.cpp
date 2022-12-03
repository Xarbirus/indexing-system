#include "app/src/input_processor/command_processor/clear_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/remove_root_result.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

clear_processor::clear_processor(std::string _command, engine& engine)
  : command_info{std::move(_command), "Use '{}' to remove everything from the index."}
  , m_engine{engine}
{}

void clear_processor::execute(std::string_view arguments)
{
  if(!arguments.empty())
  {
    print_to_user("Extra argument!\n", description);
    return;
  }

  const auto result = m_engine.get().clear_roots();
  const auto duration = to_user_string(result.duration);
  print_to_user(fmt::format("Finished in {}.", duration));
  LOG_INFO("Index was cleared ({}).", duration);
}

std::string_view clear_processor::get_description() const noexcept
{
  return description;
}