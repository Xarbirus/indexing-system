get_filename_component(target_name ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${target_name}
  main.cpp)

target_link_libraries(${target_name}
  PRIVATE
    logger)

set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${APP_NAME})
