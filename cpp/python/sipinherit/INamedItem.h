#pragma once
#include <memory>

// Interface for named item
class INamedItem {
public:
  virtual ~INamedItem() = default;

  virtual const char * name() const = 0;
};

using INamedItemSptr = std::shared_ptr<INamedItem>;
