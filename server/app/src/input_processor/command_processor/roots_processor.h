#pragma once

#include "app/src/input_processor/command_processor/command_info.h"
#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class roots_processor : public command_processor, private command_info
{
public:
  roots_processor(std::string _command, engine& engine);

  void execute(std::string_view) override;

  [[nodiscard]] std::string_view get_description() const noexcept override;

private:
  engine& m_engine;
};
