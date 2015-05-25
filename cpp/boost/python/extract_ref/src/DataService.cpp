#include "DataService.h"

void DataService::add(const std::string & name,
                      const WorkspaceSharedPtr & value) {
  std::cout << "Use count: " << value.use_count() << "\n";
  m_index.insert(std::make_pair(name, value));
}

void DataService::remove(const std::string & name) {
  m_index.erase(name);
}

WorkspaceSharedPtr DataService::get(const std::string & name) {
  return m_index[name];
}

std::size_t DataService::size() const {
  return m_index.size();
}

void DataService::clear() {
  m_index.clear();
}
