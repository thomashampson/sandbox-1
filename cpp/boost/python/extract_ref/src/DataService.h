#ifndef DATASERVICE_H_
#define DATASERVICE_H_

#include "DataObjects.h"

class DataService {
public:
  void add(const std::string & name,
           const WorkspaceSharedPtr & value);
  void remove(const std::string & name);
  void clear();
  WorkspaceSharedPtr get(const std::string & name);
  std::size_t size() const;

private:
  std::map<std::string, WorkspaceSharedPtr> m_index;
};

#endif // DATASERVICE_H_
