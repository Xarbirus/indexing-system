#include "app/src/misc/spinlock.h"

void spinlock::lock() noexcept
{
  for(;;)
  {
    if(!m_lock.test_and_set(std::memory_order_acquire))
      return;

    while(m_lock.test(std::memory_order_relaxed))
      __builtin_ia32_pause();
  }
}

bool spinlock::try_lock() noexcept
{
  return !m_lock.test(std::memory_order_relaxed) && !m_lock.test_and_set(std::memory_order_acquire);
}

void spinlock::unlock() noexcept
{
  m_lock.clear(std::memory_order_release);
}