#include "app/src/grpc/index_service.h"

#include "app/src/grpc/converters/index_holder_results.h"
#include "app/src/engine/engine.h"

#include "logger/src/logger.h"

index_service::index_service(engine& engine)
  : m_engine{engine}
{}

rpc::add_root_result index_service::add_root_impl(const rpc::root& root)
{
  LOG_INFO("Grpc server called, root - {}.", root.value());
  return to_grpc(m_engine.add_root(root.value()));
}

rpc::remove_root_result index_service::remove_root_impl(const rpc::root& root)
{
  LOG_INFO("Grpc server called, root - {}.", root.value());
  return to_grpc(m_engine.remove_root(root.value()));
}

rpc::get_roots_result index_service::get_roots_impl(const rpc::empty&)
{
  LOG_INFO("Grpc server called.");

  return to_grpc(m_engine.get_roots());
}

rpc::remove_root_result index_service::clear_roots_impl(const rpc::empty&)
{
  LOG_INFO("Grpc server called.");
  return to_grpc(m_engine.clear_roots());
}

rpc::get_files_result index_service::get_files_impl(const rpc::get_files_request& request)
{
  LOG_INFO("Grpc server called, word - {}.", request.word());
  return to_grpc(m_engine.get_files(request.word()));
}

rpc::get_files_result index_service::get_files_in_root_impl(const rpc::get_files_in_root_request& request)
{
  LOG_INFO("Grpc server called, word - {}, root - {}.", request.word(), request.root());
  return to_grpc(m_engine.get_files(request.word(), request.root()));
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

grpc::Status index_service::get_files(grpc::ServerContext*, const rpc::get_files_request* request, rpc::get_files_result* response)
{
  return process(&index_service::get_files_impl, *request, *response);
}

grpc::Status index_service::get_files_in_root(grpc::ServerContext*, const rpc::get_files_in_root_request* request, rpc::get_files_result* response)
{
  return process(&index_service::get_files_in_root_impl, *request, *response);
}
