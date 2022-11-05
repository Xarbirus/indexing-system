#pragma once

#include <string>

class command_processor
{
public:
  virtual ~command_processor() = default;

  virtual void execute(const std::string&) = 0;

  [[nodiscard]] virtual std::string get_description() const = 0;
};
