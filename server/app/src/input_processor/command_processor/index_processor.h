#pragma once

#include "app/src/input_processor/command_processor/command_processor.h"

class engine;

class index_processor : public command_processor
{
public:
  explicit index_processor(engine& engine);

  void execute(const std::string& arguments) override;

  [[nodiscard]] std::string get_description() const override;

private:
  engine& m_engine;

  static constexpr auto description = "Use 'index <absolute_path_to_directory>' to start indexing the directory.";
};
