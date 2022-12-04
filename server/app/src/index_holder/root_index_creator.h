#pragma once

#include "app/src/index_holder/root_index.h"

#include "app/src/misc/spinlock.h"

#include <future>

class task_dispatcher;

class root_index::creator
{
  friend class root_index;

public:
  creator(std::atomic_bool& stop_flag, task_dispatcher& dispatcher, const std::filesystem::path& root, const std::string& root_string);

private:
  static std::string read_file(const std::filesystem::path& path);

  void add_file(const std::filesystem::path& path);
  void add_directory(const std::filesystem::path& path);

  std::atomic_bool& m_stop_flag;
  task_dispatcher& m_dispatcher;

  std::list<std::future<void>> m_statuses;
  spinlock m_spin;

  std::filesystem::path m_root;
  std::string m_original_root;

  std::mutex m_files_mutex;
  std::mutex m_symbols_mutex;

  filenames_storage m_files;
  symbols m_symbols;

  std::locale m_current_locale;
};