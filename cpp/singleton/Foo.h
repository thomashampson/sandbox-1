#ifndef FOO_H_
#define FOO_H_

#include "FooModule.h"
#include "SingletonHolder.h"

class DLL_PUBLIC FooImpl {
public:
  FooImpl();

};

using Foo = SingletonHolder<FooImpl>;

extern template class DLL_PUBLIC SingletonHolder<FooImpl>;


#endif // FOO_H_
