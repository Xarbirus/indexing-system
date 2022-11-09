#include "app/src/index_holder/index_holder.h"

#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/index_holder/results/remove_root_result.h"

#include "app/src/misc/benchmark.h"

#include "logger/src/logger.h"

std::filesystem::path index_holder::prepare_filepath(std::string path)
{
  if(path[0] == '~')
  {
    auto* home = std::getenv("HOME");
    if(home or (home = std::getenv("USERPROFILE")))
      path.replace(0, 1, home);
    else
    {
      constexpr auto message = "Can't find '~' in environment variables.";
      LOG_WARNING(message);
      throw std::runtime_error{fmt::format("{} Please, change the directory or set '~'.", message)};
    }
  }
  LOG_DEBUG("Get the path '{}' for processing.", path);

  std::filesystem::path prepared_path{path};

  if(!exists(prepared_path))
  {
    constexpr auto message = "'{}' does not exist.";
    LOG_WARNING(message, prepared_path.c_str());
    throw std::runtime_error{fmt::format("{} Please, use an existing directory.", fmt::format(message, prepared_path.c_str()), message)};
  }

  if(!is_directory(prepared_path))
  {
    constexpr auto message = "'{}' is not a directory.";
    LOG_WARNING(message, prepared_path.c_str());
    throw std::runtime_error{fmt::format("{} Please, use a path to a directory.", fmt::format(message, prepared_path.c_str()), message)};
  }

  if(!prepared_path.is_absolute())
  {
    constexpr auto message = "'{}' is not an absolute path.";
    LOG_WARNING(message, prepared_path.c_str());
    throw std::runtime_error{fmt::format("{} Please, use an absolute path.", fmt::format(message, prepared_path.c_str()), message)};
  }

  return prepared_path;
}

index_holder::index_holder(task_dispatcher& dispatcher)
  : m_dispatcher{dispatcher}
{}

add_root_result index_holder::add_root(const std::string& root)
{
  add_root_result out;

  auto adder = [&]()
  {
    auto temp = root_index::create(m_dispatcher, prepare_filepath(root), root);

    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&root](const auto& current_root) { return current_root.is_equivalent(root); });
    out.files = m_roots.emplace_back(std::move(temp)).get_number_of_files();
  };
  out.duration = benchmark(adder);

  return out;
}

remove_root_result index_holder::remove_root(const std::string& root)
{
  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([prepared_root=prepare_filepath(root)](const auto& current_root) { return current_root.is_equivalent(prepared_root); });
  };
  return {benchmark(remover)};
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
  out.duration = benchmark(reader);

  return out;
}

remove_root_result index_holder::clear_roots()
{
  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.clear();
  };
  return {benchmark(remover)};
}
