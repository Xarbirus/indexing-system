#include "app/src/input_processor/command_processor/remove_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/remove_root_result.h"
#include "app/src/input_processor/prepare_command.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

remove_processor::remove_processor(engine& engine)
  : m_engine{engine}
{}

void remove_processor::execute(const std::string& arguments)
{
  const auto [path, suffix] = separate_first_word(arguments);
  if(!path.empty() and suffix.empty())
  {
    const auto result = m_engine.remove_root(path);
    const auto duration = to_user_string(result.duration);
    print_to_user(fmt::format("Finished in {}.", duration));
    LOG_INFO("Removed '{}' ({}).", path, duration);
  }
  else
    print_to_user(description);
}

std::string remove_processor::get_description() const
{
  return description;
}
