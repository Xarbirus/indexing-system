#include "app/src/input_processor/command_processor/index_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/input_processor/prepare_command.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

#include <fmt/chrono.h>

index_processor::index_processor(std::string _command, engine& engine)
  : command_info{std::move(_command), "Use '{} <absolute_path_to_directory>' to start indexing the directory."}
  , m_engine{engine}
{}

void index_processor::execute(std::string_view arguments)
{
  const auto [path, suffix] = separate_first_word(arguments);
  if(!path.empty() and suffix.empty())
  {
    const auto result = m_engine.add_root(path);
    const auto duration = to_user_string(result.duration);
    print_to_user(fmt::format("Finished in {}. {} file(s) indexed.", duration, result.files));
    LOG_INFO("Indexed {} file(s) in '{}' ({}).", result.files, path, duration);
  }
  else
    print_to_user(description);
}

std::string_view index_processor::get_description() const
{
  return description;
}
