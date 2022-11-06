#include "app/src/engine/engine.h"

#include "app/src/index_holder/index_holder.h"
#include "app/src/service/service.h"

engine::engine(service& service, index_holder& index)
  : m_service{service}
  , m_index{index}
{}

void engine::stop_service()
{
  LOG_INFO("Engine stops service.");
  m_service.stop();
}

void engine::add_root(const std::filesystem::path& root, const std::string& original_root)
{
  LOG_INFO("Engine adds root '{}' ({}).", root.c_str(), original_root);
  m_index.add_root(root, original_root);
}

void engine::remove_root(const std::filesystem::path& root, const std::string& original_root)
{
  LOG_INFO("Engine removes root '{}' ({}).", root.c_str(), original_root);
  m_index.remove_root(root, original_root);
}
