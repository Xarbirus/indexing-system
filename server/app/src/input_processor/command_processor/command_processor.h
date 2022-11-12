#pragma once

#include <string>

class command_processor
{
public:
  virtual ~command_processor() = default;

  virtual void execute(std::string_view) = 0;

  [[nodiscard]] virtual std::string_view get_description() const = 0;
};
