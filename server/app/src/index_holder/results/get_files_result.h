#pragma once

#include "app/src/index_holder/file_info.h"

#include <chrono>
#include <vector>

struct get_files_result
{
  struct root_info
  {
    std::string root_path;
    std::vector<file_info> files;
  };

  std::vector<root_info> roots;
  std::chrono::system_clock::duration duration;
};
