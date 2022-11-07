#pragma once

#include <chrono>

struct add_root_result
{
  std::size_t number_of_files{};
  std::chrono::minutes duration;
};
