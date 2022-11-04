#pragma once

#include "app/details/engine.h"
#include "app/details/input_processor.h"
#include "app/details/service_base.h"
#include "app/details/task_dispatcher.h"

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
