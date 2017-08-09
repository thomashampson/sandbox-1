#include "MplAxes.h"
#include "NDArray1D.h"

namespace Python {

void MplAxes::plot(const std::vector<double> &x, const std::vector<double> &y,
                   const char *format) {
  NDArray1D xnp(x), ynp(y);
  PyObject_CallMethod(this->get(), "plot", "(OOs)", xnp.get(), ynp.get(),
                      format);
}
}
