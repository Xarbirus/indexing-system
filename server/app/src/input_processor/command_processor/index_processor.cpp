#include "app/src/input_processor/command_processor/index_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/input_processor/prepare_command.h"
#include "app/src/input_processor/command_processor/prepare_filepath.h"
#include "app/src/misc/duration_to_string.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

#include <fmt/chrono.h>

index_processor::index_processor(engine& engine)
  : m_engine{engine}
{}

void index_processor::execute(const std::string& arguments)
{
  const auto [path, suffix] = separate_first_word(arguments);
  if(!path.empty() and suffix.empty())
  {
    if(const auto prepared_path = prepare_filepath(path))
    {
      const auto result = m_engine.add_root(*prepared_path, path);
      const auto duration = to_user(result.duration);
      print_to_user(fmt::format("Finished in {} . {} file(s) indexed.", duration, result.files));
      LOG_INFO("Indexed {} file(s) in '{}' ({}).", result.files, path, duration);
    }
  }
  else
    print_to_user(description);
}

std::string index_processor::get_description() const
{
  return description;
}
