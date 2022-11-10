set(tests_name ${TARGET_NAME}-gtests)

add_executable(${tests_name}
  filenames_storage_tests.cpp
  prepare_command_tests.cpp
  to_user_string_tests.cpp

  ../src/index_holder/filenames_storage.cpp
  ../src/index_holder/filenames_storage.h
  ../src/input_processor/prepare_command.cpp
  ../src/input_processor/prepare_command.h
  ../src/misc/duration_to_string.cpp
  ../src/misc/duration_to_string.h)

target_link_libraries(${tests_name}
  PRIVATE
    Boost::boost
    fmt::fmt
    GTest::gtest
    GTest::gtest_main)

set_target_properties(${tests_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_TESTS_OUTPUT_DIRECTORY})
