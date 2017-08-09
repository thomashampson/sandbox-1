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

  /**
   * Plot lines or markers to the axes
   * @param x A container of X points. Requires support for forward iteration.
   * @param y A container of Y points. Requires support for forward iteration.
   * @param format A format string for the line/markers
   */
  void plot(const std::vector<double> &x, const std::vector<double> &y,
            const char *format);
};
}
#endif // MPLAXES_H
