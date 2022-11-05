#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class quit_processor : public command_processor
{
public:
  explicit quit_processor(engine& engine);

  void execute(const std::string&) override;

  [[nodiscard]] std::string get_description() const override;

private:
  engine& m_engine;

  static constexpr auto description = "Use 'quit' to stop the service.";
};
