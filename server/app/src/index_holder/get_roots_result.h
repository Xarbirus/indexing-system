#pragma once

#include <chrono>
#include <string>
#include <vector>

struct get_roots_result
{
  std::vector<std::string> roots;
  std::chrono::minutes duration;
};
