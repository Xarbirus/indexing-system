#include "app/src/grpc/converters/index_holder_results.h"

namespace
{
  template<typename T>
  void fill_duration(T& message, const std::chrono::system_clock::duration& duration)
  {
    message.mutable_duration()->set_seconds(floor<std::chrono::seconds>(duration).count());
  }
}

rpc::add_root_result to_grpc(const add_root_result& value)
{
  rpc::add_root_result out;
  out.set_files(value.files);
  fill_duration(out, value.duration);
  return out;
}

rpc::get_files_result to_grpc(const get_files_result& value)
{
  rpc::get_files_result out;
  for(const auto& root : value.roots)
  {
    auto* added = out.add_roots();
    added->set_root_path(root.root_path);

    auto file_info_adder = [&](const auto& file)
    {
      auto* file_info = added->add_files();
      file_info->set_filename(file.filename);
      file_info->set_word_counter(file.word_counter);
    };
    std::for_each(root.files.begin(), root.files.end(), file_info_adder);
  }
  fill_duration(out, value.duration);
  return out;
}

rpc::get_roots_result to_grpc(const get_roots_result& value)
{
  rpc::get_roots_result out;
  std::for_each(value.roots.begin(), value.roots.end(), [&](const auto& root){ out.add_roots(root); });
  fill_duration(out, value.duration);
  return out;
}

rpc::remove_root_result to_grpc(const remove_root_result& value)
{
  rpc::remove_root_result out;
  fill_duration(out, value.duration);
  return out;
}
