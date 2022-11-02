#include "app/details/input_processor.h"

#include "logger/src/logger.h"

#include <iostream>

void input_processor::run() noexcept
{
  std::string str;
  while(std::getline(std::cin, str))
  {
    try
    {
      if(str.empty())
        continue;

      std::cout << str << std::endl;
    }
    catch(const std::exception& ex)
    {
      LOG_ERROR("Input processor caught an exception: {}, resuming", ex.what());
    }
    catch(...)
    {
      LOG_ERROR("Input processor caught an unknown exception, resuming");
    }
  }

  LOG_ERROR("Input processor ended");
}
