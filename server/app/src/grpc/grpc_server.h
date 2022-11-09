#pragma once

#include <future>
#include <list>
#include <memory>
#include <string>

namespace grpc
{
  class Server;
  class ServerBuilder;
  class Service;
}

class engine;

class grpc_server
{
public:
  grpc_server(const std::string& address, engine& engine);
  ~grpc_server();

  void start();
  void stop();

private:
  std::future<void> m_stop_done;

  std::unique_ptr<grpc::ServerBuilder> m_builder;
  std::list<std::unique_ptr<grpc::Service>> m_services;
  std::unique_ptr<grpc::Server> m_server;
};

