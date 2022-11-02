#include "app/service.h"
#include "logger/src/logger.h"
#include "logger/src/logger_defines.h"

int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {
    logger::reset(logger::default_log_path,
                  logger::default_log_size,
                  logger::default_log_files,
                  logger::default_log_level);

    service().run();
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("server caught an exception: {}", ex.what());
    return EXIT_FAILURE;
  }
  catch(...)
  {
    LOG_ERROR("server caught an unknown exception");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
