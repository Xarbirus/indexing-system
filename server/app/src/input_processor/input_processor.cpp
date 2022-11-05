#include "app/src/input_processor/input_processor.h"

#include "app/src/engine/engine.h"
#include "app/src/input_processor/prepare_command.h"
#include "app/src/input_processor/prepare_filepath.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

#include <iostream>

input_processor::input_processor(engine& engine)
  : m_commands{{"help", {&input_processor::help, "Use this command WITHOUT ARGUMENTS to find out how does indexing system work."}},
               {"index", {&input_processor::index, "Use this command WITH ONE ARGUMENT (path to directory) to start indexing the directory."}},
               {"quit", {&input_processor::quit, "Use this command WITHOUT ARGUMENTS to stop the service."}}}
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
    print_to_user("Available commands:");
    for(const auto& command : m_commands)
      print_to_user('\t', command.first, '\t', command.second.description);
  };

  if(current_command.size() != 2)
    print_common_help();
  else
  {
    if(auto it = m_commands.find(current_command[1]); it != m_commands.end())
      print_to_user(it->second.description);
    else
      print_common_help();
  }
}

void input_processor::index(const std::vector<std::string>& current_command)
{
  if(current_command.size() == 2)
  {
    auto prepared_path = prepare_filepath(current_command[1]);
    m_engine.add_root(prepared_path);
  }
  else
    print_to_user(m_commands.at("index").description);
}

void input_processor::quit(const std::vector<std::string>&)
{
  stop();
  m_engine.stop_service();
}
