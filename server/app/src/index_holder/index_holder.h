#pragma once

#include "app/src/index_holder/root_index.h"

#include <shared_mutex>

class index_holder
{
public:
  void add_root(const std::filesystem::path& root, const std::string& original_root);
  void remove_root(const std::filesystem::path& root, const std::string& original_root);

private:
  std::shared_mutex m_mutex;
  std::list<root_index> m_roots;
};
