add_executable(${TARGET_NAME}
  main.cpp

  service/service.cpp
  service/service.h
  service/service_base.cpp
  service/service_base.h

  engine/engine.cpp
  engine/engine.h
  input_processor/input_processor.cpp
  input_processor/input_processor.h
  input_processor/prepare_command.cpp
  input_processor/prepare_command.h
  task_dispatcher/task_dispatcher.cpp
  task_dispatcher/task_dispatcher.h)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    Boost::boost
    logger)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${APP_NAME})
