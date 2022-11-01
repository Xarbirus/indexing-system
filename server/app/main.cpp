#include "logger/logger.h"
#include "logger/logger_defines.h"

int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {
    logger::reset(logger::default_log_path,
                  logger::default_log_size,
                  logger::default_log_files,
                  logger::default_log_level);
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
