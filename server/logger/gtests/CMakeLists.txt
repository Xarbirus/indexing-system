set(tests_name ${TARGET_NAME}-gtests)

set(source_list
  filename_tests.cpp
  lambda_tests.cpp
  simple_function_tests.cpp
  template_function_tests.cpp

  details/check_message.cpp
  details/check_message.h)

add_executable(${tests_name} ${source_list})

target_link_libraries(${tests_name}
  PRIVATE
    GTest::gtest
    GTest::gtest_main
    logger)

set_target_properties(${tests_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TESTS_OUTPUT_DIRECTORY})
