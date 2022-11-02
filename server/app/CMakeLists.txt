get_filename_component(target_name ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${target_name}
  main.cpp
  service.cpp
  service.h

  details/input_processor.cpp
  details/input_processor.h
  details/task_dispatcher.cpp
  details/task_dispatcher.h
  details/service_base.cpp
  details/service_base.h)

target_link_libraries(${target_name}
  PRIVATE
    Boost::boost
    logger)

set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${APP_NAME})
