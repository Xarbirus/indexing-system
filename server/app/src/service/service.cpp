#include "app/src/service/service.h"

service::service(service_configuration&& cfg)
  : m_cfg{std::move(cfg)}
  , m_tasks{get_number_of_tasks()}
  , m_index{m_tasks}
  , m_engine{*this, m_index}
  , m_input{m_engine}
  , m_server{m_cfg.server_address, m_engine}
{}

void service::initialize()
{
  m_input.start();
  m_server.start();
}

void service::finalize()
{
  m_input.stop();
  m_server.stop();
}

unsigned service::get_number_of_tasks() noexcept
{
  constexpr unsigned max_threads = 8;
  const auto threads = std::thread::hardware_concurrency();
  return threads > max_threads ? max_threads : threads;
}