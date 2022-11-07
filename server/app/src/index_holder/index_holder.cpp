#include "app/src/index_holder/index_holder.h"

#include "app/src/index_holder/add_root_result.h"
#include "app/src/index_holder/remove_root_result.h"

#include "app/src/misc/benchmark.h"

index_holder::index_holder(task_dispatcher& dispatcher)
  : m_dispatcher{dispatcher}
{}

add_root_result index_holder::add_root(const std::filesystem::path& root, const std::string& original_root)
{
  add_root_result out;

  auto adder = [&]()
  {
    root_index temp{m_dispatcher, root, original_root};

    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&root](const auto& current_root){ return current_root.is_equivalent(root); });
    out.number_of_files = m_roots.emplace_back(std::move(temp)).get_number_of_files();
  };

  out.duration = benchmark<std::chrono::minutes>(adder);
  return out;
}

remove_root_result index_holder::remove_root(const std::filesystem::path& root, const std::string&)
{
  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&root](const auto& current_root){ return current_root.is_equivalent(root); });
  };
  return {benchmark<std::chrono::minutes>(remover)};
}
