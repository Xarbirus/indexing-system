#pragma once

#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/index_holder/results/remove_root_result.h"

#include "index.pb.h"

rpc::add_root_result to_grpc(const add_root_result& value);
rpc::get_roots_result to_grpc(const get_roots_result& value);
rpc::remove_root_result to_grpc(const remove_root_result& value);
