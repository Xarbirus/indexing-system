get_filename_component(proto_module_name "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
set(proto_generated_name ${proto_module_name}_generated)

generate_grpc_source(${proto_module_name} ${proto_generated_name})

generate_grpc_target(grpc-${proto_module_name} ${${proto_generated_name}})
