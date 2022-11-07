#pragma once

#include <chrono>
#include <functional>

template<typename T, typename Fcn, typename... Args>
T benchmark(Fcn&& fcn, Args&&... args)
{
  const auto start = std::chrono::system_clock::now();
  std::invoke(std::forward<Fcn>(fcn), std::forward<Args>(args)...);
  const auto finish = std::chrono::system_clock::now();
  return std::chrono::duration_cast<T>(finish - start);
}