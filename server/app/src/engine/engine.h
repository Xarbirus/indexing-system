#pragma once

#include <filesystem>

struct add_root_result;
struct remove_root_result;
class index_holder;
class service;

class engine
{
public:
  engine(service& service, index_holder& index);

  void stop_service();

  add_root_result add_root(const std::filesystem::path& root, const std::string& original_root);
  remove_root_result remove_root(const std::filesystem::path& root, const std::string& original_root);

private:
  service& m_service;
  index_holder& m_index;
};
