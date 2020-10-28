#pragma once

#include "INamedItem.h"
#include <vector>

// Store instances of named items
class NamedItemRegistry {
public:
  static void subscribe(INamedItemSptr item);

private:
  std::vector<INamedItemSptr> m_items;
};
