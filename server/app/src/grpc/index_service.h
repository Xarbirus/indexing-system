#pragma once

#include "grpc-helpers/src/grpc_call_processor.h"

#include "generated/grpc/index.grpc.pb.h"

class engine;

class index_service : public rpc::index_service::Service, private grpc_call_processor<index_service>
{
  friend class grpc_call_processor<index_service>;

public:
  explicit index_service(engine& engine);

  grpc::Status add_root(grpc::ServerContext*, const rpc::root*, rpc::add_root_result*) override;
  grpc::Status remove_root(grpc::ServerContext*, const rpc::root*, rpc::remove_root_result*) override;
  grpc::Status get_roots(grpc::ServerContext*, const rpc::empty*, rpc::get_roots_result*) override;
  grpc::Status clear_roots(grpc::ServerContext*, const rpc::empty*, rpc::remove_root_result*) override;
  grpc::Status get_files(grpc::ServerContext*, const rpc::get_files_request*, rpc::get_files_result*) override;
  grpc::Status get_files_in_root(grpc::ServerContext*, const rpc::get_files_in_root_request*, rpc::get_files_result*) override;

private:
  [[nodiscard]] rpc::add_root_result add_root_impl(const rpc::root& request);
  [[nodiscard]] rpc::remove_root_result remove_root_impl(const rpc::root& request);
  [[nodiscard]] rpc::get_roots_result get_roots_impl(const rpc::empty& request);
  [[nodiscard]] rpc::remove_root_result clear_roots_impl(const rpc::empty& request);
  [[nodiscard]] rpc::get_files_result get_files_impl(const rpc::get_files_request& request);
  [[nodiscard]] rpc::get_files_result get_files_in_root_impl(const rpc::get_files_in_root_request& request);

  engine& m_engine;
};
