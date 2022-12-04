#include "app/src/input_processor/input_processor.h"

#include "app/src/input_processor/prepare_command.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

#include <thread>
#include <iostream>

input_processor::input_processor(engine& engine)
  : m_commands{engine}
{}

void input_processor::start()
{
  print_to_user("Service started.");

  auto user_input = [&commands=m_commands]
  {
    std::string line;
    while(std::getline(std::cin, line))
    {
      try
      {
        LOG_DEBUG("Input processor gets line '{}'.", line);
        const auto [command, arguments] = prepare_command(line);
        commands.execute(command, arguments);
      }
      catch(const std::exception& ex)
      {
        print_to_user("ERROR: {}.", ex.what());
        LOG_ERROR("Input processor caught an exception: {}, resuming.", ex.what());
      }
      catch(...)
      {
        print_to_user("ERROR: unexpected problem.");
        LOG_ERROR("Input processor caught an unknown exception, resuming.");
      }
    }
  };
  std::thread(user_input).detach();
}

void input_processor::stop()
{
  std::cin.setstate(std::ios_base::eofbit);
  print_to_user("Input processor ended.");
}
