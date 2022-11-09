#pragma once

#include "app/src/grpc/grpc_call_processor.h"

#include "index.grpc.pb.h"

class engine;

class index_service : public rpc::index_service::Service, private grpc_call_processor<index_service>
{
  friend class grpc_call_processor<index_service>;

public:
  explicit index_service(engine& engine);

  grpc::Status add_root(grpc::ServerContext* context, const rpc::root* request, rpc::add_root_result* response) override;
  grpc::Status remove_root(grpc::ServerContext* context, const rpc::root* request, rpc::remove_root_result* response) override;
  grpc::Status get_roots(grpc::ServerContext* context, const rpc::empty* request, rpc::get_roots_result* response) override;
  grpc::Status clear_roots(grpc::ServerContext* context, const rpc::empty* request, rpc::remove_root_result* response) override;

private:
  rpc::add_root_result add_root_impl(const rpc::root& request);
  rpc::remove_root_result remove_root_impl(const rpc::root& request);
  rpc::get_roots_result get_roots_impl(const rpc::empty& request);
  rpc::remove_root_result clear_roots_impl(const rpc::empty& request);

  engine& m_engine;
};
