set(source_list
  logger.cpp
  logger.h
  logger_defines.h
  logger_levels.h
  details/format_pattern.cpp
  details/format_pattern.h)

set(lib_type STATIC)

add_library(${TARGET_NAME}
  ${lib_type}
  ${source_list})

target_link_libraries(${TARGET_NAME}
  PUBLIC
    spdlog::spdlog)
