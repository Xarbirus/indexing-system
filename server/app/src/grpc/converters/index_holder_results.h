#pragma once

#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/index_holder/results/get_files_result.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/index_holder/results/remove_root_result.h"

#include "index.pb.h"

[[nodiscard]] rpc::add_root_result to_grpc(const add_root_result& value);
[[nodiscard]] rpc::get_files_result to_grpc(const get_files_result& value);
[[nodiscard]] rpc::get_roots_result to_grpc(const get_roots_result& value);
[[nodiscard]] rpc::remove_root_result to_grpc(const remove_root_result& value);
