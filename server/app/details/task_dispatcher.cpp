#include "app/details/task_dispatcher.h"

task_dispatcher::task_dispatcher(std::size_t thread_count)
  : m_work(m_io.get_executor())
{
  LOG_INFO("starting task dispatcher");

  for(std::size_t i = 0; i < thread_count; ++i)
    m_workers.emplace_back([this] { do_work(); });
  LOG_INFO("task dispatcher uses {} threads", thread_count);
}

task_dispatcher::~task_dispatcher()
{
  try
  {
    LOG_INFO("stopping task dispatcher");

    m_work.reset();
    m_io.stop();

    for(auto& worker : m_workers)
      worker.join();

    LOG_INFO("task dispatcher stopped");
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("task dispatcher failed to stop: {}", ex.what());
  }
  catch(...)
  {
    LOG_ERROR("task dispatcher failed to stop: unknown exception");
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
      LOG_ERROR("worker catches '{}', restart", ex.what());
    }
    catch(...)
    {
      LOG_ERROR("worker catches unknown error, restart");
    }
  }
}
