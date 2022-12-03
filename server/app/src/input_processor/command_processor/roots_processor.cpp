#include "app/src/input_processor/command_processor/roots_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

roots_processor::roots_processor(std::string _command, engine& engine)
  : command_info{std::move(_command), "Use '{}' to get all indexed roots."}
  , m_engine{engine}
{}

void roots_processor::execute(std::string_view arguments)
{
  if(!arguments.empty())
  {
    print_to_user("Extra argument!\n", description);
    return;
  }

  const auto result = m_engine.get().get_roots();
  const auto duration = to_user_string(result.duration);
  print_to_user(fmt::format("Finished in {}.", duration));
  print_to_user("Available roots:");
  for(const auto& root : result.roots)
    print_to_user("\t", root);
  LOG_INFO("Find {} roots ({}).", result.roots.size(), duration);
}

std::string_view roots_processor::get_description() const noexcept
{
  return description;
}
