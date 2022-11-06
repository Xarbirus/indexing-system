#include "app/src/input_processor/command_processor/remove_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/input_processor/prepare_command.h"
#include "app/src/input_processor/command_processor/prepare_filepath.h"
#include "app/src/misc/print_to_user.h"

remove_processor::remove_processor(engine& engine)
  : m_engine{engine}
{}

void remove_processor::execute(const std::string& arguments)
{
  const auto [path, suffix] = separate_first_word(arguments);
  if(!path.empty() and suffix.empty())
  {
    if(const auto prepared_path = prepare_filepath(path))
      m_engine.remove_root(*prepared_path);
  }
  else
    print_to_user(description);
}

std::string remove_processor::get_description() const
{
  return description;
}
