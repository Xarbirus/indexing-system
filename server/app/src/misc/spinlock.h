#pragma once

#include <atomic>

class spinlock
{
public:
  void lock() noexcept;
  bool try_lock() noexcept;

  void unlock() noexcept;

private:
  std::atomic_flag m_lock;
};