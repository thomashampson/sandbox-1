#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <vector>

class ContainerIterator;

class Container {

public:
  Container();
  ContainerIterator begin() const;
  ContainerIterator end() const;

  std::size_t size() const { return m_data.size(); }

private:
  std::vector<double> m_data;
};

#endif // CONTAINER_H_
