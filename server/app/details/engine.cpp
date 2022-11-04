#include "app/details/engine.h"

#include "app/service.h"

engine::engine(service& service)
  : m_service{service}
{}

void engine::stop_service()
{
  m_service.stop();
}
