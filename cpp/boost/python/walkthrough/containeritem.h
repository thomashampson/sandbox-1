#ifndef CONTAINERITEM_H_
#define CONTAINERITEM_H_
#include <cstdint>
#include <boost/iterator/iterator_facade.hpp>

class Container;
class ContainerIterator;

class ContainerItem {
public:
  void advance(int64_t delta) {
    m_index = delta < 0 ? std::max(static_cast<uint64_t>(0),
                                   static_cast<uint64_t>(m_index) + delta)
                        : std::min(m_container.size(),
                                   m_index + static_cast<size_t>(delta));
  }

  void incrementIndex() {
    if (m_index < m_container.size()) {
      ++m_index;
    }
  }

  void decrementIndex() {
    if (m_index > 0) {
      --m_index;
    }
  }

  size_t index() const { return m_index; }

private:
  friend class ContainerIterator;

  /// Private constructor, can only be created by HistogramIterator
  ContainerItem(const Container &container, const size_t index)
      : m_container(container), m_index(index) {}

  const Container &m_container;
  std::size_t m_index;
};

#endif // CONTAINERITEM_H_
