#pragma once

#include "logger/src/logger.h"

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>
#include <future>
#include <thread>
#include <vector>

class task_dispatcher
{
public:
  explicit task_dispatcher(std::size_t thread_count);
  ~task_dispatcher();

  template<typename Callable, typename R = std::invoke_result_t<Callable>>
  std::future<R> add_task(Callable&& task) const
  {
    LOG_DEBUG("adding task to dispatcher");
    std::packaged_task<R()> package(std::forward<Callable>(task));
    auto result = package.get_future();
    boost::asio::post(m_work.get_executor(), std::move(package));
    return result;
  }

private:
  void do_work();

  boost::asio::io_context m_io;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_work;
  std::vector<std::thread> m_workers;
};
