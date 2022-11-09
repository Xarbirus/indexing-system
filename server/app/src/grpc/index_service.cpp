#include "app/src/grpc/index_service.h"

#include "app/src/grpc/converters/index_holder_results.h"

#include "app/src/engine/engine.h"

index_service::index_service(engine& engine)
  : m_engine{engine}
{}

rpc::add_root_result index_service::add_root_impl(const rpc::root& root)
{
  return to_grpc(m_engine.add_root(root.value()));
}

rpc::remove_root_result index_service::remove_root_impl(const rpc::root& root)
{
  return to_grpc(m_engine.remove_root(root.value()));
}

rpc::get_roots_result index_service::get_roots_impl(const rpc::empty&)
{
  return to_grpc(m_engine.get_roots());
}

rpc::remove_root_result index_service::clear_roots_impl(const rpc::empty&)
{
  return to_grpc(m_engine.clear_roots());
}

grpc::Status index_service::add_root(grpc::ServerContext*, const rpc::root* request, rpc::add_root_result* response)
{
  return process(&index_service::add_root_impl, *request, *response);
}

grpc::Status index_service::remove_root(grpc::ServerContext*, const rpc::root* request, rpc::remove_root_result* response)
{
  return process(&index_service::remove_root_impl, *request, *response);
}

grpc::Status index_service::get_roots(grpc::ServerContext*, const rpc::empty* request, rpc::get_roots_result* response)
{
  return process(&index_service::get_roots_impl, *request, *response);
}

grpc::Status index_service::clear_roots(grpc::ServerContext*, const rpc::empty* request, rpc::remove_root_result* response)
{
  return process(&index_service::clear_roots_impl, *request, *response);
}
