get_filename_component(APP_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${GENERATED_GRPC_DIRECTORY})

add_subdirectory(app)
add_subdirectory(logger)
