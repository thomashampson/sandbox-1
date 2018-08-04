#include "Foo.h"

#include <iostream>

FooImpl::FooImpl() {
  std::cerr << "Foo instance=" << this << "\n";
}

template class SingletonHolder<FooImpl>;
