#include "app/src/engine/engine.h"

#include "app/src/service/service.h"

engine::engine(service& service)
  : m_service{service}
{}

void engine::stop_service()
{
  LOG_INFO("Engine stops service.");
  m_service.stop();
}

void engine::add_root(const std::filesystem::path& path)
{
  LOG_INFO("Engine adds root '{}'.", path.c_str());
}

void engine::remove_root(const std::filesystem::path& path)
{
  LOG_INFO("Engine removes root '{}'.", path.c_str());
}
