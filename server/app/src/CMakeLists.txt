add_executable(${TARGET_NAME}
  main.cpp

  engine/engine.cpp
  engine/engine.h

  grpc/grpc_server.cpp
  grpc/grpc_server.h
  grpc/index_service.cpp
  grpc/index_service.h
  grpc/converters/index_holder_results.h
  grpc/converters/index_holder_results.cpp

  index_holder/file_info.h
  index_holder/filenames_storage.cpp
  index_holder/filenames_storage.h
  index_holder/index_holder.cpp
  index_holder/index_holder.h
  index_holder/root_index.cpp
  index_holder/root_index.h
  index_holder/root_index_creator.cpp
  index_holder/root_index_creator.h
  index_holder/results/add_root_result.h
  index_holder/results/get_files_result.h
  index_holder/results/get_roots_result.h
  index_holder/results/remove_root_result.h

  input_processor/commands_holder.cpp
  input_processor/commands_holder.h
  input_processor/input_processor.cpp
  input_processor/input_processor.h
  input_processor/prepare_command.cpp
  input_processor/prepare_command.h
  input_processor/command_processor/clear_processor.cpp
  input_processor/command_processor/clear_processor.h
  input_processor/command_processor/command_info.cpp
  input_processor/command_processor/command_info.h
  input_processor/command_processor/command_processor.h
  input_processor/command_processor/index_processor.cpp
  input_processor/command_processor/index_processor.h
  input_processor/command_processor/help_processor.cpp
  input_processor/command_processor/help_processor.h
  input_processor/command_processor/quit_processor.cpp
  input_processor/command_processor/quit_processor.h
  input_processor/command_processor/remove_processor.cpp
  input_processor/command_processor/remove_processor.h
  input_processor/command_processor/roots_processor.cpp
  input_processor/command_processor/roots_processor.h

  misc/benchmark.h
  misc/duration_to_string.cpp
  misc/duration_to_string.h
  misc/print_to_user.h
  misc/spinlock.cpp
  misc/spinlock.h

  service/service.cpp
  service/service.h
  service/service_base.cpp
  service/service_base.h
  service/service_configuration.h

  task_dispatcher/task_dispatcher.cpp
  task_dispatcher/task_dispatcher.h)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    Boost::boost
    grpc-helpers
    grpc-index
    logger)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${APP_NAME})
