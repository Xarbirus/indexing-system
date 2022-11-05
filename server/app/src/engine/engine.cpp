#include "app/src/engine/engine.h"

#include "app/src/service/service.h"

engine::engine(service& service)
  : m_service{service}
{}

void engine::stop_service()
{
  m_service.stop();
}
