#include "app/src/index_holder/index_holder.h"

#include "app/src/index_holder/results/add_root_result.h"
#include "app/src/index_holder/results/get_files_result.h"
#include "app/src/index_holder/results/get_roots_result.h"
#include "app/src/index_holder/results/remove_root_result.h"

#include "app/src/misc/benchmark.h"
#include "app/src/misc/spinlock.h"

#include "logger/src/logger.h"

#include <execution>
#include <memory>

#define ADD_WAITER                                  \
  if(m_stop.load(std::memory_order_acquire))        \
    throw std::runtime_error{"Service is stopped."}; \
  std::shared_lock lock{m_request_started};

std::filesystem::path index_holder::prepare_filepath(std::string path)
{
  if(path.empty())
  {
    constexpr auto message = "Can't use empty path.";
    LOG_WARNING(message);
    throw std::runtime_error{fmt::format("{} Please, change the directory.", message)};
  }

  if(path[0] == '~')
  {
    auto* home = std::getenv("HOME");
    if(!home)
    {
      home = std::getenv("USERPROFILE");
      if(!home)
      {
        constexpr auto message = "Can't find '~' in environment variables.";
        LOG_WARNING(message);
        throw std::runtime_error{fmt::format("{} Please, change the directory or set '~'.", message)};
      }
    }
    path.replace(0, 1, home);
  }
  LOG_DEBUG("Get the path '{}' for processing.", path);

  std::filesystem::path prepared_path(std::move(path));

  if(!exists(prepared_path))
  {
    constexpr auto message = "'{}' does not exist.";
    LOG_WARNING(message, prepared_path.string());
    throw std::runtime_error{fmt::format("{} Please, use an existing directory.", fmt::format(message, prepared_path.string()), message)};
  }

  if(!is_directory(prepared_path))
  {
    constexpr auto message = "'{}' is not a directory.";
    LOG_WARNING(message, prepared_path.string());
    throw std::runtime_error{fmt::format("{} Please, use a path to a directory.", fmt::format(message, prepared_path.string()), message)};
  }

  if(!prepared_path.is_absolute())
  {
    constexpr auto message = "'{}' is not an absolute path.";
    LOG_WARNING(message, prepared_path.string());
    throw std::runtime_error{fmt::format("{} Please, use an absolute path.", fmt::format(message, prepared_path.string()), message)};
  }

  return prepared_path;
}

index_holder::index_holder(task_dispatcher& dispatcher)
  : m_dispatcher{dispatcher}
{}

void index_holder::stop()
{
  m_stop.store(true, std::memory_order_release);

  std::scoped_lock waiter{m_request_started};
}

add_root_result index_holder::add_root(const std::string& root)
{
  ADD_WAITER;

  LOG_INFO("Adding root '{}'.", root);

  add_root_result out;

  auto adder = [&]()
  {
    auto prepared_root = prepare_filepath(root);
    auto temp = root_index::create(m_stop, m_dispatcher, prepared_root, root);

    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([&](const auto& current) { return current.is_equivalent(prepared_root); });
    out.files = m_roots.emplace_back(std::move(temp)).get_number_of_files();
  };
  out.duration = benchmark(adder);

  return out;
}

remove_root_result index_holder::remove_root(const std::string& root)
{
  ADD_WAITER;

  LOG_INFO("Removing root '{}'.", root);

  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.remove_if([prepared_root = prepare_filepath(root)](const auto& current) { return current.is_equivalent(prepared_root); });
  };
  return {benchmark(remover)};
}

get_roots_result index_holder::get_roots() const
{
  ADD_WAITER;

  LOG_INFO("Getting all roots.");

  get_roots_result out;

  auto reader = [&]()
  {
    std::shared_lock lock{m_mutex};
    out.roots.reserve(m_roots.size());
    std::transform(m_roots.begin(),
                   m_roots.end(),
                   std::back_inserter(out.roots),
                   [](const auto& root) { return root.get_original_root(); });
  };
  out.duration = benchmark(reader);

  return out;
}

remove_root_result index_holder::clear_roots()
{
  ADD_WAITER;

  LOG_INFO("Removing all roots.");

  auto remover = [&]()
  {
    std::scoped_lock lock{m_mutex};
    m_roots.clear();
  };
  return {benchmark(remover)};
}

get_files_result index_holder::get_files(const std::string& word) const
{
  ADD_WAITER;

  LOG_INFO("Getting files with '{}'.", word);

  get_files_result out;

  auto reader = [&]()
  {
    spinlock spin;
    auto filler = [&](const auto& root) mutable
    {
      auto files = root.get_files_info(word);
      std::scoped_lock lock{spin};
      out.roots.emplace_back(root.get_original_root(), std::move(files));
    };

    std::shared_lock lock{m_mutex};
    out.roots.reserve(m_roots.size());
    std::for_each(std::execution::par, m_roots.begin(), m_roots.end(), filler);
  };
  out.duration = benchmark(reader);

  return out;
}

get_files_result index_holder::get_files(const std::string& word, const std::string& root) const
{
  ADD_WAITER;

  LOG_INFO("Getting files with '{}' in root '{}'.", word, root);

  get_files_result out;

  auto reader = [&]()
  {
    std::shared_lock lock{m_mutex};
    const auto iter =
      std::find_if(m_roots.begin(),
                   m_roots.end(),
                   [prepared_root = prepare_filepath(root)](const auto& current) { return current.is_equivalent(prepared_root); });
    if(iter != m_roots.end())
      out.roots.emplace_back(root, iter->get_files_info(word));
  };
  out.duration = benchmark(reader);

  return out;
}
