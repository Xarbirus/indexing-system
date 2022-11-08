function(generate_grpc_target target_name)
  add_library(${target_name} OBJECT ${ARGN})
  target_link_libraries(${target_name} PRIVATE gRPC::gRPC)

  if(NOT STATIC)
    set_property(TARGET ${target_name} PROPERTY POSITION_INDEPENDENT_CODE ON)
  endif()
endfunction()
