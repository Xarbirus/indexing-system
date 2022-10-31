set(module_root_dir ${CMAKE_CURRENT_LIST_DIR})
get_filename_component(target_name ${module_root_dir} NAME)

include_directories(${module_root_dir})

add_executable(${target_name}
  app/main.cpp

  logger/logger.cpp
  logger/logger.h)

target_link_libraries(${target_name}
  fmt::fmt
  spdlog::spdlog)
