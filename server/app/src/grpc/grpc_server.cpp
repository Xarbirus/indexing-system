#include "app/src/grpc/grpc_server.h"

#include "app/src/grpc/index_service.h"

#include "logger/src/logger.h"

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

grpc_server::grpc_server(const std::string& address, engine& engine)
  : m_builder{std::make_unique<grpc::ServerBuilder>()}
{
  LOG_DEBUG("Creating grpc service.");
  m_builder->RegisterService(m_services.emplace_back(std::make_unique<index_service>(engine)).get());
  m_builder->AddChannelArgument(GRPC_ARG_ENABLE_HTTP_PROXY, 0);
  m_builder->AddListeningPort(address, grpc::InsecureServerCredentials());
  LOG_INFO("Grpc server listens {}.", address);
}

grpc_server::~grpc_server() = default;

void grpc_server::start()
{
  try
  {
    LOG_DEBUG("Starting grpc server.");
    if(!m_server)
    {
      m_server = m_builder->BuildAndStart();
      if(!m_server)
        throw std::runtime_error("Cannot start grpc server");
      m_stop_done = std::async(std::launch::async, [&]() { m_server->Wait(); });
      LOG_INFO("grpc server started.");
    }
    else
      LOG_WARNING("grpc server has started already.");
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("grpc server failed to start: {}.", ex.what());
    throw;
  }
}

void grpc_server::stop()
{
  try
  {
    LOG_DEBUG("Stopping grpc server.");
    if(m_server)
    {
      m_server->Shutdown();
      m_stop_done.get();
      m_server.reset();
      LOG_INFO("grpc server stopped.");
    }
    else
      LOG_WARNING("grpc server hasn't started.");
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("grpc server failed to stop: {}.", ex.what());
    throw;
  }
}
