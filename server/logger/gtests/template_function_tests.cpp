#include "logger/gtests/details/check_message.h"

#include <gtest/gtest.h>

class template_function_tests : public ::testing::Test
{
protected:
  template_function_tests()
  {
    msg.source.filename = "foo.cpp";
    msg.source.line = 42;
  }

  spdlog::details::log_msg msg;

  static constexpr auto master_value_template = " [foo.cpp:42:{}]";
};


TEST_F(template_function_tests, function_templates)
{
  {
    constexpr auto function_name = "bar";

    auto full_function_name = fmt::format("int {}(T) [with T = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int {}(T) [with T = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int B::{}(T) [with T = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int B::{}(T<F>) [with T = foo; F = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }
}

TEST_F(template_function_tests, class_templates)
{
  {
    constexpr auto function_name = "A<T>::bar";

    auto full_function_name = fmt::format("int {}() [with T = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A<T>::bar";

    auto full_function_name = fmt::format("int B::{}() [with T = int]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A<T>::bar";

    auto full_function_name = fmt::format("int B::{}(R) [with T = int; R = bool]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A<T(R)>::bar";

    auto full_function_name = fmt::format("int C::B::{}(int) [with T = int; R = bool]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }

  {
    constexpr auto function_name = "A::bar";

    auto full_function_name = fmt::format("int C::B<T(R)>::{}(int) [with T = int; R = bool]", function_name);
    msg.source.funcname = full_function_name.data();
    check(msg, fmt::format(master_value_template, function_name));
  }
}

