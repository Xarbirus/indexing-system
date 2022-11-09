#include "app/src/input_processor/prepare_command.h"

#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>

namespace
{
  void update_test_set_to_upper(std::vector<std::string>& test_set, std::pair<std::string, std::string>& master)
  {
    boost::to_upper(master.second);

    for(std::size_t i = 0, end = test_set.size(); i < end; i++)
      test_set.push_back(boost::to_upper_copy(test_set[i]));
  }

#define COMPARE(command, result)                 \
  {                                              \
    EXPECT_EQ(result, prepare_command(command)); \
  }
}

TEST(prepare_command, empty)
{
  const std::pair<std::string, std::string> empty_command{"", ""};
  std::vector<std::string> empty_test_set{"", "   "};
  std::for_each(empty_test_set.cbegin(), empty_test_set.cend(), [&](const auto& command) { COMPARE(command, empty_command); });
}

TEST(prepare_command, to_lower)
{
  const std::pair<std::string, std::string> single_command{"help", ""};
  std::vector<std::string> test_set{"help"};
  test_set.emplace_back("HELP");
  test_set.emplace_back("HElp");
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command) { COMPARE(command, single_command); });
}

TEST(prepare_command, trim)
{
  std::pair<std::string, std::string> single_command{"help", ""};
  std::vector<std::string> test_set{"   help", "help   ", "   help   "};
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command) { COMPARE(command, single_command); });

  const auto shift = test_set.size();
  update_test_set_to_upper(test_set, single_command);
  auto test_start = test_set.cbegin();
  std::advance(test_start, shift);
  std::for_each(test_start, test_set.cend(), [&](const auto& command) { COMPARE(command, single_command); });
}

TEST(prepare_command, separate_first)
{
  std::pair<std::string, std::string> complex_command{"help", "foo bar"};
  std::vector<std::string> test_set{"help foo bar", "help   foo bar", "  help   foo bar  "};
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command) { COMPARE(command, complex_command); });

  const auto shift = test_set.size();
  update_test_set_to_upper(test_set, complex_command);
  auto test_start = test_set.cbegin();
  std::advance(test_start, shift);
  std::for_each(test_start, test_set.cend(), [&](const auto& command) { COMPARE(command, complex_command); });
}

TEST(prepare_command, inner_whitespace)
{
  std::pair<std::string, std::string> complex_command{"help", "foo   bar"};
  std::vector<std::string> test_set{"help foo   bar", "help   foo   bar", "  help   foo   bar  "};
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command) { COMPARE(command, complex_command); });

  const auto shift = test_set.size();
  update_test_set_to_upper(test_set, complex_command);
  auto test_start = test_set.cbegin();
  std::advance(test_start, shift);
  std::for_each(test_start, test_set.cend(), [&](const auto& command) { COMPARE(command, complex_command); });
}

TEST(prepare_command, long_command)
{
  std::pair<std::string, std::string> master_very_long_command{"it", "s a very long command"};
  std::vector<std::string> test_set{"   it s a very long command   "};
  std::for_each(test_set.cbegin(), test_set.cend(), [&](const auto& command) { COMPARE(command, master_very_long_command); });

  const auto shift = test_set.size();
  update_test_set_to_upper(test_set, master_very_long_command);
  auto test_start = test_set.cbegin();
  std::advance(test_start, shift);
  std::for_each(test_start, test_set.cend(), [&](const auto& command) { COMPARE(command, master_very_long_command); });
}
