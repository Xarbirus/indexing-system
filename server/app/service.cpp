#include "app/service.h"

service::service()
  : m_tasks{get_number_of_tasks()}
{}

void service::initialize()
{
  m_tasks.add_task([&]{ m_input.run(); });
}

void service::finalize() {}

unsigned service::get_number_of_tasks() noexcept
{
  constexpr unsigned max_threads = 8;
  const auto threads = std::thread::hardware_concurrency();
  return threads > max_threads ? max_threads : threads;
}