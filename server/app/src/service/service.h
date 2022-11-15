#pragma once

#include "app/src/engine/engine.h"
#include "app/src/grpc/grpc_server.h"
#include "app/src/index_holder/index_holder.h"
#include "app/src/input_processor/input_processor.h"
#include "app/src/service/service_base.h"
#include "app/src/service/service_configuration.h"
#include "app/src/task_dispatcher/task_dispatcher.h"

class service : public service_base
{
public:
  explicit service(service_configuration&& cfg);

private:
  void initialize() override;
  void finalize() override;

  static unsigned get_number_of_tasks() noexcept;

  service_configuration m_cfg;
  task_dispatcher m_tasks;
  index_holder m_index;
  engine m_engine;
  input_processor m_input;
  index_grpc_server m_server;
};
