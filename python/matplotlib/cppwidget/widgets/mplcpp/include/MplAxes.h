#ifndef MPLAXES_H
#define MPLAXES_H

#include "PythonObject.h"

#include <vector>

namespace Python {

/**
 * @brief MplAxes wraps the matplotlib.axes type for convenience.
 * It declares much functionality of the corresponding mpl class
 */
class MplAxes : public PythonObject {
public:
  using PythonObject::PythonObject;

  template <typename XArrayType, typename YArrayType>
  void plot(const XArrayType &x, const YArrayType &y, const char *format);
};
}
#endif // MPLAXES_H
