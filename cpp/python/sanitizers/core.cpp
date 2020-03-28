#include "core.hpp"

namespace core {

  std::string hello() {
    int *p = new int;
    delete p;
    *p = 5;
    return "Hello Python 3!";
  }

}
