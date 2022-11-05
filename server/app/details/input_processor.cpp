#include "app/details/input_processor.h"
#include "app/details/engine.h"
#include "app/details/prepare_command.h"

#include "logger/src/logger.h"

#include <iostream>

input_processor::input_processor(engine& engine)
  : m_commands{{"quit", {&input_processor::quit, "Use this command without arguments to stop the service."}},
               {"help", {&input_processor::help, "Use this command without arguments to find out how does indexing system work."}}}
  , m_engine{engine}
{}

void input_processor::run() noexcept
{
  std::string line;
  while(std::getline(std::cin, line))
  {
    try
    {
      LOG_DEBUG("Input processor gets line '{}'", line);

      if(line.empty())
        continue;

      process_command(prepare_command(line));
    }
    catch(const std::exception& ex)
    {
      LOG_ERROR("Input processor caught an exception: {}, resuming", ex.what());
    }
    catch(...)
    {
      LOG_ERROR("Input processor caught an unknown exception, resuming");
    }
  }

  LOG_ERROR("Input processor ended");
}

void input_processor::stop()
{
  std::cin.setstate(std::ios_base::eofbit);
}

void input_processor::process_command(const std::vector<std::string>& current_command)
{
  if(auto it = m_commands.find(current_command[0]); it != m_commands.end())
    std::invoke(it->second.processor, this, current_command);
  else
    help(current_command);
}

void input_processor::help(const std::vector<std::string>& current_command)
{
  auto print_common_help = [&]()
  {
    std::cout << "Available commands:\n";
    for(const auto& command : m_commands)
      std::cout << '\t' << command.first << '\t' << command.second.description << std::endl;
  };

  if(current_command.size() != 2)
    print_common_help();
  else
  {
    if(auto it = m_commands.find(current_command[1]); it != m_commands.end())
      std::cout << it->second.description << std::endl;
    else
      print_common_help();
  }
}

void input_processor::quit(const std::vector<std::string>&)
{
  stop();
  m_engine.stop_service();
}
