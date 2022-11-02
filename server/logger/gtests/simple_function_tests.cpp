#include "logger/gtests/details/check_message.h"

#include <gtest/gtest.h>

class simple_function_tests : public ::testing::Test
{
protected:
  simple_function_tests()
  {
    msg.source.filename = "foo.cpp";
    msg.source.line = 42;
  }

  spdlog::details::log_msg msg;

  static constexpr auto master_value_template = " [foo.cpp:42:{}]";
};

TEST_F(simple_function_tests, without_args)
{
  constexpr auto function_name = "bar";

  auto full_function_name = fmt::format("void {}()", function_name);
  msg.source.funcname = full_function_name.data();
  check(msg, fmt::format(master_value_template, function_name));
}

TEST_F(simple_function_tests, with_args)
{
  constexpr auto function_name = "bar";

  auto full_function_name = fmt::format("int {}(int, bool)", function_name);
  msg.source.funcname = full_function_name.data();
  check(msg, fmt::format(master_value_template, function_name));
}

TEST_F(simple_function_tests, with_namespace)
{
  {
    constexpr auto function_name = "{anonymous}::bar";

    auto full_function_name = fmt::format("int {}(int, bool)", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int {}(int, bool)", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int B::{}(int, bool)", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int C::B::{}(int, bool)", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }
}
