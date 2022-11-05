#pragma once

#include <filesystem>

class service;

class engine
{
public:
  explicit engine(service& service);

  void stop_service();

  void add_root(const std::filesystem::path& root);
  void remove_root(const std::filesystem::path& root);

private:
  service& m_service;
};
