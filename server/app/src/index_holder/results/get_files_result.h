#pragma once

#include <chrono>
#include <map>
#include <string>
#include <vector>

struct get_files_result
{
  struct root_info
  {
    std::string root_path;
    std::vector<std::string> files;
  };

  std::vector<root_info> roots;
  std::chrono::system_clock::duration duration;
};
