#include "app/src/task_dispatcher/task_dispatcher.h"

#include "logger/src/logger.h"

task_dispatcher::task_dispatcher(std::size_t thread_count)
  : m_work(m_io.get_executor())
{
  LOG_INFO("Starting task dispatcher.");

  m_workers.reserve(thread_count);
  for(std::size_t i = 0; i < thread_count; ++i)
    m_workers.emplace_back([this] { do_work(); });
  LOG_DEBUG("Task dispatcher uses {} threads.", thread_count);
}

task_dispatcher::~task_dispatcher()
{
  try
  {
    LOG_INFO("Stopping task dispatcher.");

    m_work.reset();
    m_io.stop();

    for(auto& worker : m_workers)
      worker.join();

    LOG_INFO("Task dispatcher stopped.");
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("Task dispatcher failed to stop: {}.", ex.what());
  }
  catch(...)
  {
    LOG_ERROR("Task dispatcher failed to stop: unknown exception.");
  }
}

void task_dispatcher::do_work()
{
  while(true)
  {
    try
    {
      m_io.run();
      break;
    }
    catch(const std::exception& ex)
    {
      LOG_ERROR("Worker caught '{}', restarting.", ex.what());
    }
    catch(...)
    {
      LOG_ERROR("Worker caught unknown error, restarting.");
    }
  }
}
