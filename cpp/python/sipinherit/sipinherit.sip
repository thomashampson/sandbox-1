%Module sipinherit

class INamedItem {
%TypeHeaderCode
#include "INamedItem.h"
%End

public:
  virtual const char* name() const = 0;
};

class NamedItemRegistry {
%TypeHeaderCode
#include "NamedItemRegistry.h"
#include "extract.h"
#include <memory>
%End

public:
  static void subscribe(SIP_PYOBJECT);
  %MethodCode
    auto pyNamedItem = PyObject_CallObject(a0, nullptr);
    if(pyNamedItem) {
      auto cppNamedItem = extract<INamedItem>(BorrowedRef(pyNamedItem));
      NamedItemRegistry::subscribe(INamedItemSptr(cppNamedItem));
    } else {
      sipIsErr = 1;
    }
  %End

private:
  NamedItemRegistry(const NamedItemRegistry &);
};