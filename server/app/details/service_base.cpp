#include "app/details/service_base.h"

#include "logger/src/logger.h"

service_base::service_base()
  : m_signals(m_io)
{
  init_default_signal_handlers();
  init_interruption_handlers();

  async_wait_for_signal();
}

void service_base::run()
{
  std::exception_ptr saved_exception;
  try
  {
    LOG_INFO("Starting indexing service");
    initialize();

    m_io.run();  // blocks
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("indexing service failed to run: {}", ex.what());
    saved_exception = std::current_exception();
  }

  try
  {
    finalize();
    LOG_INFO("indexing service event loop finished");
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("indexing service failed to finalize: {}", ex.what());
    saved_exception = std::current_exception();
  }

  if(saved_exception)
    std::rethrow_exception(saved_exception);
}

void service_base::set_signal_handler(int signal_number, signal_handler handler)
{
  try
  {
    m_signals.add(signal_number);
    m_signal_handlers[signal_number] = std::move(handler);
  }
  catch(const std::exception& ex)
  {
    LOG_WARNING("Failed to add a handler for the signal {}: {}", signal_number, ex.what());
  }
}

service_base::signal_handler service_base::get_interruption_handler()
{
  return [this]
  {
    LOG_DEBUG("indexing service: termination requested");
    m_io.stop();
  };
}

void service_base::init_default_signal_handlers()
{
  constexpr std::array signal_numbers{SIGTTIN, SIGTTOU, SIGTSTP, SIGPIPE};

  const auto handler = SIG_IGN;
  for(const auto signal_number : signal_numbers)
    std::signal(signal_number, handler);
}

void service_base::init_interruption_handlers()
{
  constexpr std::array signal_numbers{SIGTERM, SIGABRT, SIGILL, SIGSEGV, SIGBUS, SIGQUIT, SIGINT, SIGTSTP};

  auto handler = get_interruption_handler();
  for(const auto signal_number : signal_numbers)
    set_signal_handler(signal_number, handler);
}

void service_base::async_wait_for_signal()
{
  auto handler = [this](const auto& error, auto signal_number) { on_signal_received(error, signal_number); };
  m_signals.async_wait(std::move(handler));
}

void service_base::on_signal_received(const boost::system::error_code& error, const int signal_number)
{
  if(!error)
    process_signal(signal_number);

  async_wait_for_signal();
}

void service_base::process_signal(int signal_number)
{
  LOG_DEBUG("Signal received: {}", signal_number);

  const auto it = m_signal_handlers.find(signal_number);
  if(it == std::cend(m_signal_handlers))
    return;

  try
  {
    it->second();
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("Failed to process the signal: {}", ex.what());
  }
}
