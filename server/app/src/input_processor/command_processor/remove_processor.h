#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class remove_processor : public command_processor
{
public:
  explicit remove_processor(engine& engine);

  void execute(const std::string& arguments) override;

  [[nodiscard]] std::string get_description() const override;

private:
  engine& m_engine;

  static constexpr auto description = "Use 'remove <absolute_path_to_directory>' to remove the directory from the index.";
};
