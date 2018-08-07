#include "container.h"
#include "containeriterator.h"

Container::Container() : m_data{1., 2., 3.} {

}

ContainerIterator Container::begin() const {
  return ContainerIterator(*this, 0);
}

ContainerIterator Container::end() const {
  return ContainerIterator(*this, this->size());
}
