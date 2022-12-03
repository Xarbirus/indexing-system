#pragma once

#include "app/src/input_processor/command_processor/command_info.h"
#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class index_processor : public command_processor, private command_info
{
public:
  index_processor(std::string _command, engine& engine);

  void execute(std::string_view arguments) override;

  [[nodiscard]] std::string_view get_description() const noexcept override;

private:
  std::reference_wrapper<engine> m_engine;
};
