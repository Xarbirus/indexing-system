#include "logger/gtests/details/check_message.h"

#include <gtest/gtest.h>

class filename_tests : public ::testing::Test
{
protected:
  filename_tests()
  {
    msg.source.funcname = "<lambda()>";
    msg.source.line = 42;
  }

  static void check(const spdlog::details::log_msg& message)
  {
    ::check(message, master_value);
  }

  spdlog::details::log_msg msg;

  static constexpr auto master_value = " [foo.cpp:42:lambda]";
};

#ifdef _WIN32
TEST_F(filename_tests, windows)
{
  msg.source.filename = "foo.cpp";
  check(msg);

  msg.source.filename = "C:\\root\\foo.cpp";
  check(msg);

  msg.source.filename = "C:\\root\\dir\\foo.cpp";
  check(msg);

  msg.source.filename = "C:\\root\\dir\\..\\foo.cpp";
  check(msg);

  msg.source.filename = "..\\dir\\foo.cpp";
  check(msg);
}
#else
TEST_F(filename_tests, linux)
{
  msg.source.filename = "foo.cpp";
  check(msg);

  msg.source.filename = "/root/foo.cpp";
  check(msg);

  msg.source.filename = "/root/dir/foo.cpp";
  check(msg);

  msg.source.filename = "/root/dir/../foo.cpp";
  check(msg);

  msg.source.filename = "../dir/foo.cpp";
  check(msg);
}
#endif
