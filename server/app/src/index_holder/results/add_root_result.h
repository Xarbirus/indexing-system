#pragma once

#include <chrono>

struct add_root_result
{
  std::size_t files{};
  std::chrono::system_clock::duration duration;
};
