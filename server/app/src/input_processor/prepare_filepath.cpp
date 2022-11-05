#include "app/src/input_processor/prepare_filepath.h"

#include "app/src/input_processor/string_processing.h"

std::filesystem::path prepare_filepath(std::string_view path)
{
  trim(path);

  return path;
}