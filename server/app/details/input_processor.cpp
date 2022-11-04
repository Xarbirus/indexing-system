#include "app/details/input_processor.h"
#include "app/details/engine.h"

#include "logger/src/logger.h"

#include <boost/algorithm/string.hpp>

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

std::vector<std::string> input_processor::prepare_command(std::string str)
{
  LOG_DEBUG("Input processor gets line '{}'", str);

  static constexpr auto whitespaces = " \t\n\r\v\f";

  boost::to_lower(str);
  std::string_view trimmed{str};

  trimmed.remove_prefix(std::min(trimmed.find_first_not_of(whitespaces), trimmed.size()));
  if(auto suffix = trimmed.find_last_not_of(whitespaces); suffix != std::string::npos)
    trimmed.remove_suffix(trimmed.size() - suffix - 1);

  std::vector<std::string> args;
  boost::split(args, trimmed, boost::is_any_of(whitespaces), boost::token_compress_on);

  LOG_DEBUG("Input processor prepares command of {} elements", args.size());

  return args;
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
