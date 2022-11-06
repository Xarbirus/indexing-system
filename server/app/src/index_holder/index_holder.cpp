#include "app/src/index_holder/index_holder.h"

void index_holder::add_root(const std::filesystem::path& root, const std::string& original_root)
{
  root_index temp{root, original_root};

  std::scoped_lock lock{m_mutex};
  auto it = std::find_if(m_roots.begin(), m_roots.end(), [&root](const auto& current_root){ return current_root.is_equivalent(root); });
  if(it != m_roots.cend())
    *it = std::move(temp);
  else
    m_roots.emplace_back(std::move(temp));
}

void index_holder::remove_root(const std::filesystem::path& root, const std::string&)
{
  std::scoped_lock lock{m_mutex};
  m_roots.remove_if([&root](const auto& current_root){ return current_root.is_equivalent(root); });
}
