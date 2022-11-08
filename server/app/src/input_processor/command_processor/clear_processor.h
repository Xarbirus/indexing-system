#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class clear_processor : public command_processor
{
public:
  explicit clear_processor(engine& engine);

  void execute(const std::string&) override;

  [[nodiscard]] std::string get_description() const override;

private:
  engine& m_engine;

  static constexpr auto description = "Use 'clear' to remove everything from the index.";
};
