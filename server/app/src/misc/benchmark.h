#pragma once

#include <chrono>
#include <functional>

template<typename Fcn, typename... Args>
[[nodiscard]] std::chrono::system_clock::duration benchmark(Fcn&& fcn, Args&&... args)
{
  const auto start = std::chrono::system_clock::now();
  std::invoke(std::forward<Fcn>(fcn), std::forward<Args>(args)...);
  const auto finish = std::chrono::system_clock::now();
  return finish - start;
}