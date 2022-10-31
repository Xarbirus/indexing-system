#include "logger/logger.h"

int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {
    logger::reset("server.log", 1'000'000, 10);
  }
  catch(const std::exception& e)
  {
    return EXIT_FAILURE;
  }
  catch(...)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
