#include "NamedItemRegistry.h"
#include <iostream>

void NamedItemRegistry::subscribe(INamedItemSptr item) {
  std::cerr << "Subscribing " << item->name() << "\n";
}
