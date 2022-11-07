#pragma once

#include "app/src/index_holder/root_index.h"

#include <shared_mutex>

struct add_root_result;
struct remove_root_result;
class task_dispatcher;

class index_holder
{
public:
  explicit index_holder(task_dispatcher& dispatcher);

  add_root_result add_root(const std::filesystem::path& root, const std::string& original_root);
  remove_root_result remove_root(const std::filesystem::path& root, const std::string& original_root);

private:
  task_dispatcher& m_dispatcher;

  std::shared_mutex m_mutex;
  std::list<root_index> m_roots;
};