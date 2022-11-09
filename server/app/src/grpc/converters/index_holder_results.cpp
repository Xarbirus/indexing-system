#include "app/src/grpc/converters/index_holder_results.h"

rpc::add_root_result to_grpc(const add_root_result& value)
{
  rpc::add_root_result out;

  out.set_files(value.files);
  out.set_duration(value.duration.count());

  return out;
}

rpc::get_roots_result to_grpc(const get_roots_result& value)
{
  rpc::get_roots_result out;

  std::for_each(value.roots.begin(), value.roots.end(), [&](const auto& root){ out.add_roots(root); });
  out.set_duration(value.duration.count());

  return out;
}

rpc::remove_root_result to_grpc(const remove_root_result& value)
{
  rpc::remove_root_result out;

  out.set_duration(value.duration.count());

  return out;
}
