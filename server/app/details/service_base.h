#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>

#include <map>

class service_base
{
public:
  service_base();
  virtual ~service_base() = default;

  void run();

private:
  virtual void initialize() {}

  virtual void finalize() {}

  using signal_handler = std::function<void()>;

  void init_default_signal_handlers();
  void init_interruption_handlers();

  signal_handler get_interruption_handler();

  void set_signal_handler(int signal_number, signal_handler signal_handler);

  void on_signal_received(const boost::system::error_code& error, int signal_number);
  void process_signal(int signal_number);

  void async_wait_for_signal();

  boost::asio::io_context m_io;
  boost::asio::signal_set m_signals;
  std::map<int, signal_handler> m_signal_handlers;
};
