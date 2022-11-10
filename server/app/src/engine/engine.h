#pragma once

#include <string>

struct add_root_result;
struct get_files_result;
struct get_roots_result;
struct remove_root_result;
class index_holder;
class service;

class engine
{
public:
  engine(service& service, index_holder& index);

  void stop_service();

  add_root_result add_root(const std::string& root);
  remove_root_result remove_root(const std::string& root);

  get_roots_result get_roots() const;
  remove_root_result clear_roots();

  get_files_result get_files(const std::string& word) const;
  get_files_result get_files(const std::string& word, const std::string& root) const;

private:
  service& m_service;
  index_holder& m_index;
};
