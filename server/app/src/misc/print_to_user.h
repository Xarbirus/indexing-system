#pragma once

#include <iostream>

template<typename... Args>
void print_to_user(Args&&... args)
{
  (std::cout << ... << std::forward<Args>(args)) << std::endl;
}
