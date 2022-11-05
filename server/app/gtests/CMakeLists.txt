set(tests_name ${TARGET_NAME}_gtests)

add_executable(${tests_name}
  prepare_command_tests.cpp

  ../details/prepare_command.cpp
  ../details/prepare_command.h)

target_link_libraries(${tests_name}
  PRIVATE
    Boost::boost
    GTest::gtest
    GTest::gtest_main)

set_target_properties(${tests_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TESTS_OUTPUT_DIRECTORY})
