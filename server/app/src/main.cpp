#include "app/src/service/service.h"

#include "app/src/grpc/check_host_address.h"
#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"
#include "logger/src/logger_defines.h"

#include <filesystem>

void set_logger(char* app_path)
{
  std::filesystem::path logs_path{app_path};
  logs_path.replace_filename(logger::default_log_name);
  logger::reset(logs_path, logger::default_log_size, logger::default_log_files, logger::default_log_level);
}

int main(int argc, char* argv[])
{
  try
  {
    std::locale::global(std::locale(""));

    if(argc != 2)
    {
      print_to_user("Not enough arguments: add \"<host>:<port>\" to start.");
      return EXIT_FAILURE;
    }

    if(!is_correct_host_address(argv[1]))
    {
      print_to_user(fmt::format("Incorrect \"<host>:<port>\": {}.", argv[1]));
      return EXIT_FAILURE;
    }

    set_logger(argv[0]);

    service({argv[1]}).run();
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
