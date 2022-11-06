#pragma once

#include <filesystem>

class index_holder;
class service;

class engine
{
public:
  engine(service& service, index_holder& index);

  void stop_service();

  void add_root(const std::filesystem::path& root, const std::string& original_root);
  void remove_root(const std::filesystem::path& root, const std::string& original_root);

private:
  service& m_service;
  index_holder& m_index;
};
