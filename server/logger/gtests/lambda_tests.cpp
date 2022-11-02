#include "logger/gtests/details/check_message.h"

#include <gtest/gtest.h>

class lambda_tests : public ::testing::Test
{
protected:
  lambda_tests()
  {
    msg.source.filename = "foo.cpp";
    msg.source.line = 42;
  }

  static void check(const spdlog::details::log_msg& message)
  {
    ::check(message, master_value);
  }

  spdlog::details::log_msg msg;

  static constexpr auto master_value = " [foo.cpp:42:lambda]";
};

TEST_F(lambda_tests, without_args)
{
  msg.source.funcname = "<lambda()>";
  check(msg);
}

TEST_F(lambda_tests, with_args)
{
  msg.source.funcname = "<lambda(int, bool)>";
  check(msg);
}

TEST_F(lambda_tests, with_namespace)
{
  msg.source.funcname = "{anonymous}::<lambda())>";
  check(msg);

  msg.source.funcname = "{anonymous}::<lambda(int, bool)>";
  check(msg);

  msg.source.funcname = "bar::<lambda(int, bool)>";
  check(msg);

  msg.source.funcname = "bar::foo::<lambda(int, bool)>";
  check(msg);
}
