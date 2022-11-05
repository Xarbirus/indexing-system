#include "app/src/input_processor/command_processor/prepare_filepath.h"

#include "app/src/misc/print_to_user.h"

#include "logger/src/logger.h"

std::optional<std::filesystem::path> prepare_filepath(std::string path)
{
  if(path[0] == '~')
  {
    auto* home = getenv("HOME");
    if(home or (home = getenv("USERPROFILE")))
      path.replace(0, 1, home);
    else
    {
      constexpr auto message = "Can't find '~' in environment variables.";
      LOG_WARNING(message);
      print_to_user(message, " Please, change the directory or set '~'.");
      return std::nullopt;
    }
  }
  LOG_DEBUG("Get the path '{}' for processing.", path);

  std::filesystem::path prepared_path{path};

  if(!exists(prepared_path))
  {
    LOG_WARNING("'{}' does not exist.", prepared_path.c_str());
    print_to_user("Please, use an existing directory.");
    return std::nullopt;
  }

  if(!is_directory(prepared_path))
  {
    LOG_WARNING("'{}' is not a directory.", prepared_path.c_str());
    print_to_user("Please, use a path to a directory.");
    return std::nullopt;
  }

  if(!prepared_path.is_absolute())
  {
    LOG_WARNING("'{}' is not an absolute path.", prepared_path.c_str());
    print_to_user("Please, use an absolute path.");
    return std::nullopt;
  }

  return prepared_path;
}