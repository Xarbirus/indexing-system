add_executable(${TARGET_NAME}
  main.cpp

  engine/engine.cpp
  engine/engine.h

  index_holder/index_holder.cpp
  index_holder/index_holder.h
  index_holder/root_index.cpp
  index_holder/root_index.h

  input_processor/commands_holder.cpp
  input_processor/commands_holder.h
  input_processor/input_processor.cpp
  input_processor/input_processor.h
  input_processor/prepare_command.cpp
  input_processor/prepare_command.h
  input_processor/command_processor/command_processor.h
  input_processor/command_processor/index_processor.cpp
  input_processor/command_processor/index_processor.h
  input_processor/command_processor/help_processor.cpp
  input_processor/command_processor/help_processor.h
  input_processor/command_processor/prepare_filepath.cpp
  input_processor/command_processor/prepare_filepath.h
  input_processor/command_processor/remove_processor.cpp
  input_processor/command_processor/remove_processor.h
  input_processor/command_processor/quit_processor.cpp
  input_processor/command_processor/quit_processor.h

  misc/print_to_user.h

  service/service.cpp
  service/service.h
  service/service_base.cpp
  service/service_base.h

  task_dispatcher/task_dispatcher.cpp
  task_dispatcher/task_dispatcher.h)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    Boost::boost
    logger)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${APP_NAME})
