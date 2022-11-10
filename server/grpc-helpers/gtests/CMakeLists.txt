set(tests_name ${TARGET_NAME}-gtests)

set(source_list
  check_host_address_tests.cpp)

add_executable(${tests_name} ${source_list})

target_link_libraries(${tests_name}
  PRIVATE
    grpc-helpers
    fmt::fmt
    GTest::gtest
    GTest::gtest_main)

set_target_properties(${tests_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TESTS_OUTPUT_DIRECTORY})
