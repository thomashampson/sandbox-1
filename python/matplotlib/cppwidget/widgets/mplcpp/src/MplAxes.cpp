#include "MplAxes.h"
#include "NDArray1D.h"

namespace Python {

/**
 * Plot lines or markers to the axes
 * @param x A container of X points. Requires support for forward iteration.
 * @param y A container of Y points. Requires support for forward iteration.
 * @param format A format string for the line/markers
 */
template <typename XArrayType, typename YArrayType>
void MplAxes::plot(const XArrayType &x, const YArrayType &y,
                   const char *format) {
  NDArray1D xnp(x), ynp(y);
  PyObject_CallMethod(this->get(), "plot", "(OOs)", xnp.get(), ynp.get(),
                      format);
}

// Explicit instantations
using VectorDouble = std::vector<double>;
template void MplAxes::plot<VectorDouble, VectorDouble>(const VectorDouble &,
                                                        const VectorDouble &,
                                                        const char *);
}
