#ifndef NUMPY_H
#define NUMPY_H
/*
 * A collection of utilities for transfer of data to/from numpy arrays.
 */
#include "PythonObject.h"

namespace Python {

/**
 * Create a 1D numpy.ndarray object from the given iterable. It will work with
 * anything support std::begin()/std::end().
 * @param data A const reference to the data container
 * @return A 1D numpy.ndarray object containing the data
 */
template <typename Iterable> PythonObject copyToNDArray(const Iterable &data);
}

#endif // NUMPY_H
