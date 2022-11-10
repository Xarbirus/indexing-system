#pragma once

#include "app/src/index_holder/root_index.h"

#include <shared_mutex>

struct add_root_result;
struct get_files_result;
struct get_roots_result;
struct remove_root_result;
class task_dispatcher;

class index_holder
{
public:
  explicit index_holder(task_dispatcher& dispatcher);

  add_root_result add_root(const std::string& root);
  remove_root_result remove_root(const std::string& root);

  [[nodiscard]] get_roots_result get_roots() const;
  remove_root_result clear_roots();

  [[nodiscard]] get_files_result get_files(const std::string& word) const;
  [[nodiscard]] get_files_result get_files(const std::string& word, const std::string& root) const;

private:
  static std::filesystem::path prepare_filepath(std::string path);

  task_dispatcher& m_dispatcher;

  mutable std::shared_mutex m_mutex;
  std::list<root_index> m_roots;
};
