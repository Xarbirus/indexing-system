function(generate_grpc_source path_with_stem out)
  set(generated
    ${GENERATED_GRPC_DIRECTORY}/${path_with_stem}.grpc.pb.h
    ${GENERATED_GRPC_DIRECTORY}/${path_with_stem}.grpc.pb.cc
    ${GENERATED_GRPC_DIRECTORY}/${path_with_stem}.pb.h
    ${GENERATED_GRPC_DIRECTORY}/${path_with_stem}.pb.cc)

  set(${out} ${${out}} ${generated} PARENT_SCOPE)

  add_custom_command(
    OUTPUT ${generated}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_GRPC_DIRECTORY}
    COMMAND ${Protobuf_PROTOC_EXECUTABLE} -I${PROTOFILES_DIRECTORY} --cpp_out=${GENERATED_GRPC_DIRECTORY} ${PROTOFILES_DIRECTORY}/${path_with_stem}.proto
    COMMAND ${Protobuf_PROTOC_EXECUTABLE} -I${PROTOFILES_DIRECTORY} --grpc_out=${GENERATED_GRPC_DIRECTORY} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_PROGRAM} ${PROTOFILES_DIRECTORY}/${path_with_stem}.proto

    DEPENDS ${PROTOFILES_DIRECTORY}/${path_with_stem}.proto
    WORKING_DIRECTORY ${PROTOFILES_DIRECTORY}
    VERBATIM)

  set_source_files_properties(${generated}
    PROPERTIES
      COMPILE_FLAGS "-Wno-conversion -Wno-sign-conversion -Wno-unused-parameter -Wno-missing-declarations -Wno-missing-field-initializers")
endfunction()
