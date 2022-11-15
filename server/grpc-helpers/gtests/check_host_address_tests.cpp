#include "grpc-helpers/src/check_host_address.h"

#include <gtest/gtest.h>
#include <fmt/format.h>

#include <array>
#include <random>

#define CHECK(result, value)                                                     \
  {                                                                              \
    const auto address = value;                                                  \
    EXPECT_EQ(is_correct_host_address(address), result) << "value: " << address; \
  }

TEST(check_host_address, correct_ip)
{
  std::array ip_octets{0, 0, 0, 0};

  std::random_device rand;
  std::default_random_engine engine(rand());
  std::uniform_int_distribution<std::size_t> get_number_of_indices(1, ip_octets.size());
  std::uniform_int_distribution<std::size_t> get_index(0, ip_octets.size() - 1);
  std::uniform_int_distribution<int> random_octet(0, 255);

  CHECK(true, "0.0.0.0:8888");
  for(std::size_t test = 0; test < 1000; test++)
  {
    std::vector<std::size_t> indices(get_number_of_indices(engine), 0);
    std::generate(indices.begin(), indices.end(), [&] { return get_index(engine); });
    std::for_each(indices.begin(), indices.end(), [&](auto index) { ip_octets[index] = random_octet(engine); });

    CHECK(true, fmt::format("{}.{}.{}.{}:8888", ip_octets[0], ip_octets[1], ip_octets[2], ip_octets[3]));
    std::fill(ip_octets.begin(), ip_octets.end(), 0);
  }
  CHECK(true, "255.255.255.255:8888");
}

TEST(check_host_address, correct_localhost)
{
  static constexpr auto master_value = "localhost";

  std::string localhost{master_value};

  std::random_device rand;
  std::default_random_engine engine(rand());
  std::uniform_int_distribution<std::size_t> get_number_of_indices(1, localhost.size());
  std::uniform_int_distribution<std::size_t> get_index(0, localhost.size() - 1);

  CHECK(true, fmt::format("{}:8888", localhost));
  for(std::size_t test = 0; test < 1000; test++)
  {
    std::vector<std::size_t> indices(get_number_of_indices(engine), 0);
    std::generate(indices.begin(), indices.end(), [&] { return get_index(engine); });
    std::for_each(indices.begin(), indices.end(), [&](auto index) { localhost[index] = std::toupper(localhost[index], std::locale()); });

    CHECK(true, fmt::format("{}:8888", localhost));
    localhost = master_value;
  }
}

TEST(check_host_address, correct_port)
{
  std::random_device rand;
  std::default_random_engine engine(rand());
  std::uniform_int_distribution<std::size_t> get_port(0, 65535);

  for(std::size_t test = 0; test < 10000; test++)
    CHECK(true, fmt::format("localhost:{}", get_port(engine)));
}

TEST(check_host_address, incorrect_parts)
{
  EXPECT_FALSE(is_correct_host_address(""));
  EXPECT_FALSE(is_correct_host_address("127.0.0.1"));
  EXPECT_FALSE(is_correct_host_address("127.0.0.1:"));
  EXPECT_FALSE(is_correct_host_address("localhost:"));
  EXPECT_FALSE(is_correct_host_address("localhost:"));
  EXPECT_FALSE(is_correct_host_address("8888"));
  EXPECT_FALSE(is_correct_host_address(":8888"));
  EXPECT_FALSE(is_correct_host_address("...:8888"));
  EXPECT_FALSE(is_correct_host_address(".0.0.0:8888"));
  EXPECT_FALSE(is_correct_host_address("0.0.0.:8888"));
  EXPECT_FALSE(is_correct_host_address("0..0.0:8888"));
  EXPECT_FALSE(is_correct_host_address("0.0..0:8888"));
  EXPECT_FALSE(is_correct_host_address("8888:localhost"));
  EXPECT_FALSE(is_correct_host_address("8888:8888"));
  EXPECT_FALSE(is_correct_host_address("localhost:localhost"));
  EXPECT_FALSE(is_correct_host_address("localhost:888.8"));
  EXPECT_FALSE(is_correct_host_address("localhost:."));
  EXPECT_FALSE(is_correct_host_address("localhost:..."));
  EXPECT_FALSE(is_correct_host_address("localhost:0.0.0.0"));
  EXPECT_FALSE(is_correct_host_address("0.0.0.0.0:8888"));
}

TEST(check_host_address, incorrect_ip)
{
  std::array ip_octets{0, 0, 0, 0};

  std::random_device rand;
  std::default_random_engine engine(rand());
  std::uniform_int_distribution<std::size_t> get_number_of_indices(1, ip_octets.size());
  std::uniform_int_distribution<std::size_t> get_index(0, ip_octets.size() - 1);
  std::uniform_int_distribution<int> random_octet(256, 1000);

  for(std::size_t test = 0; test < 1000; test++)
  {
    std::vector<std::size_t> indices(get_number_of_indices(engine), 0);
    std::generate(indices.begin(), indices.end(), [&] { return get_index(engine); });
    std::for_each(indices.begin(), indices.end(), [&](auto index) { ip_octets[index] = random_octet(engine); });

    CHECK(false, fmt::format("{}.{}.{}.{}:8888", ip_octets[0], ip_octets[1], ip_octets[2], ip_octets[3]));
    std::fill(ip_octets.begin(), ip_octets.end(), 0);
  }
}

TEST(check_host_address, incorrect_localhost)
{
  constexpr auto max_size = 20;
  std::string localhost;

  std::random_device rand;
  std::default_random_engine engine(rand());
  std::uniform_int_distribution<std::size_t> get_number_of_chars(1, max_size);
  std::uniform_int_distribution<int> get_index(97, 122);

  for(std::size_t test = 0; test < 1000; test++)
  {
    localhost.resize(get_number_of_chars(engine));
    std::generate(localhost.begin(), localhost.end(), [&] { return static_cast<char>(get_index(engine)); });

    if(localhost != "localhost") [[likely]]
      CHECK(false, fmt::format("{}:8888", localhost));
    localhost.clear();
  }
}

TEST(check_host_address, incorrect_port)
{
  std::random_device rand;
  std::default_random_engine engine(rand());

  std::uniform_int_distribution<std::size_t> get_positive_port(65536, 100000);
  for(std::size_t test = 0; test < 10000; test++)
    CHECK(false, fmt::format("localhost:{}", get_positive_port(engine)));

  std::uniform_int_distribution<int> get_negative_port(-65535, -1);
  for(std::size_t test = 0; test < 10000; test++)
    CHECK(false, fmt::format("localhost:{}", get_negative_port(engine)));

  constexpr auto max_size = 10;
  std::string port;
  std::uniform_int_distribution<std::size_t> get_number_of_chars(1, max_size);
  std::uniform_int_distribution<std::size_t> get_index(97, 122);
  for(std::size_t test = 0; test < 1000; test++)
  {
    port.resize(get_number_of_chars(engine));
    std::generate(port.begin(), port.end(), [&] { return static_cast<char>(get_index(engine)); });
    CHECK(false, fmt::format("localhost:{}", port));
    port.clear();
  }
}