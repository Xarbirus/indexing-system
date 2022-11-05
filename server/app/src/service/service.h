#pragma once

#include "app/src/engine/engine.h"
#include "app/src/input_processor/input_processor.h"
#include "app/src/service/service_base.h"
#include "app/src/task_dispatcher/task_dispatcher.h"

class service : public service_base
{
public:
  service();

private:
  void initialize() override;
  void finalize() override;

  static unsigned get_number_of_tasks() noexcept;

  engine m_engine;
  task_dispatcher m_tasks;
  input_processor m_input;
};
