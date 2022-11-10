set(source_list
  check_host_address.cpp
  check_host_address.h
  grpc_call_processor.h
  grpc_error.h)

set(lib_type STATIC)

add_library(${TARGET_NAME}
  ${lib_type}
  ${source_list})

target_link_libraries(${TARGET_NAME}
  PUBLIC
    gRPC::gRPC)
