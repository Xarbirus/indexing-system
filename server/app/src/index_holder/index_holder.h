#pragma once

#include "app/src/index_holder/root_index.h"

#include <shared_mutex>

struct add_root_result;
struct get_roots_result;
struct remove_root_result;
class task_dispatcher;

class index_holder
{
public:
  explicit index_holder(task_dispatcher& dispatcher);

  add_root_result add_root(const std::string& root);
  remove_root_result remove_root(const std::string& root);

  get_roots_result get_roots();
  remove_root_result clear_roots();

private:
  static std::filesystem::path prepare_filepath(std::string path);

  task_dispatcher& m_dispatcher;

  std::shared_mutex m_mutex;
  std::list<root_index> m_roots;
};
