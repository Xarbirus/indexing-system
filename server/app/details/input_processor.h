#pragma once

#include <map>
#include <string>
#include <vector>

class engine;

class input_processor
{
public:
  explicit input_processor(engine& engine);

  void run() noexcept;
  void stop();

private:
  static std::vector<std::string> prepare_command(std::string str);
  void process_command(const std::vector<std::string>& command);

  void help(const std::vector<std::string>& command);
  void quit(const std::vector<std::string>& command);

  using command_processor = void(input_processor::*)(const std::vector<std::string>&);
  struct command_info
  {
    command_processor processor;
    std::string description;
  };

  const std::map<std::string, command_info> m_commands;

  engine& m_engine;
};
