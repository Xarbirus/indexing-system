#include "app/src/engine/engine.h"

#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/index_holder/index_holder.h"
#include "app/src/index_holder/results/remove_root_result.h"
#include "app/src/service/service.h"

#include "logger/src/logger.h"

engine::engine(service& service, index_holder& index)
  : m_service{service}
  , m_index{index}
{}

void engine::stop_service()
{
  LOG_INFO("Engine stops service.");
  m_service.stop();
}

add_root_result engine::add_root(const std::string& root)
{
  LOG_DEBUG("Engine adds root '{}').", root);
  return m_index.add_root(root);
}

remove_root_result engine::remove_root(const std::string& root)
{
  LOG_DEBUG("Engine removes root '{}'.", root);
  return m_index.remove_root(root);
}

get_roots_result engine::get_roots()
{
  LOG_DEBUG("Engine reads all roots.");
  return m_index.get_roots();
}

remove_root_result engine::clear_roots()
{
  LOG_DEBUG("Engine removes all roots.");
  return m_index.clear_roots();
}