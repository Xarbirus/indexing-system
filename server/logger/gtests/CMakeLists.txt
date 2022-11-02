set(tests_name ${TARGET_NAME}_gtests)

add_executable(${tests_name}
  filename_tests.cpp
  lambda_tests.cpp
  simple_function_tests.cpp
  template_function_tests.cpp

  details/check_message.cpp
  details/check_message.h)

target_link_libraries(${tests_name}
  PRIVATE
    GTest::gtest
    GTest::gtest_main
    logger)
