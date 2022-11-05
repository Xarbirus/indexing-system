#include "app/src/service/service.h"
#include "logger/src/logger.h"
#include "logger/src/logger_defines.h"

#include <filesystem>

void set_logger(char* app_path)
{
  std::filesystem::path logs_path{app_path};
  logs_path.replace_filename(logger::default_log_name);

  logger::reset(logs_path, logger::default_log_size, logger::default_log_files, logger::default_log_level);
}

int main(int /*argc*/, char* argv[])
{
  try
  {
    set_logger(argv[0]);

    service().run();
  }
  catch(const std::exception& ex)
  {
    LOG_ERROR("Server caught an exception: {}.", ex.what());
    return EXIT_FAILURE;
  }
  catch(...)
  {
    LOG_ERROR("Server caught an unknown exception.");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
