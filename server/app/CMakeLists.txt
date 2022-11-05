get_filename_component(TARGET_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TARGET_NAME}
  main.cpp
  service.cpp
  service.h

  details/engine.cpp
  details/engine.h
  details/input_processor.cpp
  details/input_processor.h
  details/prepare_command.cpp
  details/prepare_command.h
  details/task_dispatcher.cpp
  details/task_dispatcher.h
  details/service_base.cpp
  details/service_base.h)

target_link_libraries(${TARGET_NAME}
  PRIVATE
    Boost::boost
    logger)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${APP_NAME})

add_subdirectory(gtests)
