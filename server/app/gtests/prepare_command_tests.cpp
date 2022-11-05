#include "app/src/input_processor/prepare_command.h"

#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>

namespace
{
  const std::vector<std::string> single_command{"help"};

  void add_upper_to_test_set(std::vector<std::string>& test_set)
  {
    for(std::size_t i = 0, end = test_set.size(); i < end; i++)
      test_set.push_back(boost::to_upper_copy(test_set[i]));
  }

  void compare(const std::string& command, const std::vector<std::string>& result)
  {
    EXPECT_EQ(result, prepare_command(command));
  }
}

TEST(prepare_command, to_lower)
{
  std::vector<std::string> test_set{"help"};
  add_upper_to_test_set(test_set);
  test_set.emplace_back("HElp");
  std::for_each(test_set.cbegin(), test_set.cend(), [](const auto& command){ compare(command, single_command); });
}

TEST(prepare_command, trim)
{
  std::vector<std::string> test_set{"   help", "help   ", "   help   "};
  add_upper_to_test_set(test_set);
  std::for_each(test_set.cbegin(), test_set.cend(), [](const auto& command){ compare(command, single_command); });

  const std::vector<std::string> empty_command{""};
  std::vector<std::string> empty_test_set{"", "   "};
  std::for_each(empty_test_set.cbegin(), empty_test_set.cend(), [&](const auto& command){ compare(command, empty_command); });
}

TEST(prepare_command, split)
{
  const std::vector<std::string> complex_command{"help", "foo", "bar"};
  std::vector<std::string> test_set{"help foo bar", "help   foo    bar", "  help   foo    bar  "};
  add_upper_to_test_set(test_set);
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command){ compare(command, complex_command); });
}

TEST(prepare_command, long_command)
{
  constexpr auto very_long_command = "   it s a very long command   ";
  std::vector<std::string> master_very_long_command{"it", "s", "a", "very", "long", "command"};
  std::vector<std::string> test_set{very_long_command};
  add_upper_to_test_set(test_set);
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command){ compare(command, master_very_long_command); });
}
