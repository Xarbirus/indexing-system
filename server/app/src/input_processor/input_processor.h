#pragma once

#include "app/src/input_processor/commands_holder.h"

#include <map>
#include <string>
#include <vector>

class engine;

class input_processor
{
public:
  explicit input_processor(engine& engine);

  void start();
  void stop();

private:
  commands_holder m_commands;
};
