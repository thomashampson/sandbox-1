#ifndef CONTAINERITERATOR_H_
#define CONTAINERITERATOR_H_
#include "containeritem.h"

class ContainerIterator
    : public boost::iterator_facade<ContainerIterator, const ContainerItem &,
                                    boost::bidirectional_traversal_tag> {
public:
  ContainerIterator(const Container &owner, const size_t index)
      : m_item(owner, index) {}

private:
  friend class boost::iterator_core_access;

  void increment() { m_item.incrementIndex(); }

  bool equal(const ContainerIterator &other) const {
    return m_item.index() == other.m_item.index();
  }

  const ContainerItem &dereference() const { return m_item; }

  void decrement() { m_item.decrementIndex(); }

  void advance(int64_t delta) { m_item.advance(delta); }

  uint64_t distance_to(const ContainerIterator &other) const {
    return static_cast<uint64_t>(other.m_item.index()) -
           static_cast<uint64_t>(m_item.index());
  }

  ContainerItem m_item;
};

#endif // CONTAINERITERATOR_H_
