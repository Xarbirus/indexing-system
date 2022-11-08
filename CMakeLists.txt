cmake_minimum_required(VERSION 3.20)
project(indexing-system CXX)

include(cmake/definitions.cmake)
include(cmake/dirs.cmake)
include(cmake/libs.cmake)
include(cmake/proto.cmake)

add_subdirectory(server)
