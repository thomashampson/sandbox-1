#ifndef NDARRAY1D_H
#define NDARRAY1D_H

#include "PythonObject.h"
#include "Numpy.h"

namespace Python {

/**
 * Encapsulates a 1D numpy.ndarray Python object.
 *
 * Input is an iterable container. The data is copied from the input
 * to the newly created array.
 */
class NDArray1D : public PythonObject {
public:
  // inherit constructors
  using PythonObject::PythonObject;

  /**
   * Create an array from an Iterable. Iterable must support std::begin/end
   */
  template <typename Iterable>
  NDArray1D(const Iterable &data)
      : PythonObject(copyToNDArray(data)) {}
};
}

#endif // NDARRAY1D_H
