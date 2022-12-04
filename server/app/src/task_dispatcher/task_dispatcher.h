#pragma once

#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>

#include <future>
#include <thread>
#include <vector>

class task_dispatcher
{
public:
  void start(std::size_t thread_count);
  void stop();

  template<typename Callable, typename R = std::invoke_result_t<Callable>>
  std::future<R> add_task(Callable&& task) const
  {
    if(m_io.stopped())
      throw std::runtime_error{"Service is stopped."};

    std::packaged_task<R()> package(std::forward<Callable>(task));
    auto result = package.get_future();
    boost::asio::post(m_work.get_executor(), std::move(package));
    return result;
  }

private:
  void do_work();

  boost::asio::io_context m_io;
  boost::asio::executor_work_guard<boost::asio::io_context::executor_type> m_work{m_io.get_executor()};
  std::vector<std::thread> m_workers;
};
