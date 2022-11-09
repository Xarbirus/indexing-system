#include "app/src/misc/duration_to_string.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;

TEST(to_user_string, empty)
{
  EXPECT_EQ("0 minute(s) 0 second(s)", to_user_string({}));
}

TEST(to_user_string, milliseconds)
{
  auto value = to_user_string(1ms);
  EXPECT_EQ("0 minute(s) 0 second(s)", value);

  value = to_user_string(999ms);
  EXPECT_EQ("0 minute(s) 0 second(s)", value);

  value = to_user_string(1s + 1ms);
  EXPECT_EQ("0 minute(s) 1 second(s)", value);

  value = to_user_string(1s + 999ms);
  EXPECT_EQ("0 minute(s) 1 second(s)", value);
}

TEST(to_user_string, seconds)
{
  auto value = to_user_string(1s);
  EXPECT_EQ("0 minute(s) 1 second(s)", value);

  value = to_user_string(30s);
  EXPECT_EQ("0 minute(s) 30 second(s)", value);

  value = to_user_string(60s);
  EXPECT_EQ("1 minute(s) 0 second(s)", value);

  value = to_user_string(100s);
  EXPECT_EQ("1 minute(s) 40 second(s)", value);
}

TEST(to_user_string, minutes)
{
  auto value = to_user_string(1min);
  EXPECT_EQ("1 minute(s) 0 second(s)", value);

  value = to_user_string(30min);
  EXPECT_EQ("30 minute(s) 0 second(s)", value);

  value = to_user_string(60min);
  EXPECT_EQ("60 minute(s) 0 second(s)", value);

  value = to_user_string(100min);
  EXPECT_EQ("100 minute(s) 0 second(s)", value);
}