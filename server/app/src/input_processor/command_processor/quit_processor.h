#pragma once

#include "app/src/input_processor/command_processor/command_info.h"
#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class quit_processor : public command_processor, private command_info
{
public:
  quit_processor(std::string _command, engine& engine);

  void execute(std::string_view) override;

  [[nodiscard]] std::string_view get_description() const override;

private:
  engine& m_engine;
};
