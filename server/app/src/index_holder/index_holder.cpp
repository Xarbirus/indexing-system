#include "app/src/index_holder/index_holder.h"

#include "app/src/index_holder/add_root_result.h"
#include "app/src/index_holder/get_roots_result.h"
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
    auto temp = root_index::create(m_dispatcher, root, original_root);

    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&root](const auto& current_root) { return current_root.is_equivalent(root); });
    out.files = m_roots.emplace_back(std::move(temp)).get_number_of_files();
  };
  out.duration = benchmark<std::chrono::minutes>(adder);

  return out;
}

remove_root_result index_holder::remove_root(const std::filesystem::path& root, const std::string&)
{
  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&root](const auto& current_root) { return current_root.is_equivalent(root); });
  };
  return {benchmark<std::chrono::minutes>(remover)};
}

get_roots_result index_holder::get_roots()
{
  get_roots_result out;

  auto reader = [&]()
  {
    std::scoped_lock lock{m_mutex};
    out.roots.reserve(m_roots.size());
    std::transform(m_roots.begin(), m_roots.end(), std::back_inserter(out.roots), [](const auto& root){ return root.get_original_root();});
  };
  out.duration = benchmark<std::chrono::minutes>(reader);

  return out;
}

remove_root_result index_holder::clear_roots()
{
  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.clear();
  };
  return {benchmark<std::chrono::minutes>(remover)};
}
