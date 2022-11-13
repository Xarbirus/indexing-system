get_filename_component(APP_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(app)
add_subdirectory(grpc-helpers)
add_subdirectory(logger)
