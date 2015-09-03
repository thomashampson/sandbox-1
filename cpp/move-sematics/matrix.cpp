#include "matrix.h"

#include <algorithm>
#include <iostream>
#include <utility>
using std::cerr;
using std::ostream;

//---------------------- Public ------------------------------------------

// Constructor
SquareMatrix::SquareMatrix(size_t nrows)
    : m_data(allocate(nrows)), m_nrows(nrows) {
  cerr << "Constructor\n";
  // Fill
  m_data[0] = 1.0;
  for (size_t i = 1; i < nrows * nrows; ++i) {
    m_data[i] = m_data[i - 1] + 1.0;
  }
}
SquareMatrix::~SquareMatrix() { delete[] m_data; }

// Copy constructor
SquareMatrix::SquareMatrix(const SquareMatrix &other)
    : m_data(allocate(other.m_nrows)), m_nrows(other.m_nrows) {
  using std::copy;
  cerr << "Copy constructor\n";
  // Use assignment operator
  //*this = other;
  if (this != &other) {
    // size change means new memory allocation
    if (m_nrows != other.m_nrows) {
      delete[] m_data;
      m_data = allocate(other.m_nrows);
      m_nrows = other.m_nrows;
    }
    copy(other.m_data, other.m_data + m_nrows * m_nrows, m_data);
  }
}

// Copy assignment operator
SquareMatrix &SquareMatrix::operator=(const SquareMatrix &rhs) {
  using std::copy;
  cerr << "Copy-assignment operator\n";
  if (this != &rhs) {
    // size change means new memory allocation
    if (m_nrows != rhs.m_nrows) {
      delete[] m_data;
      m_data = allocate(rhs.m_nrows);
      m_nrows = rhs.m_nrows;
    }
    copy(rhs.m_data, rhs.m_data + m_nrows * m_nrows, m_data);
  }
  return *this;
}

// Move constructor
SquareMatrix::SquareMatrix(SquareMatrix &&other)
    : m_data(nullptr), m_nrows(other.m_nrows) {
  using std::swap;
  cerr << "Move constructor\n";
  //*this = std::move(rhs);
  swap(m_data, other.m_data);
  m_nrows = other.m_nrows;
}

// Move assignment operator
SquareMatrix &SquareMatrix::operator=(SquareMatrix &&rhs) {
  using std::swap;
  cerr << "Move-assignment operator\n";
  swap(m_data, rhs.m_data);
  m_nrows = rhs.m_nrows;
  return *this;
}

//---------------------- Private -----------------------------------------

double *SquareMatrix::allocate(const size_t nrows) {
  return new double[nrows * nrows];
}

//---------------------- Non-member friends ------------------------------

SquareMatrix operator*(const SquareMatrix &matrix, double scalar) {
  auto scaled = matrix;
  for (size_t i = 0; i < matrix.m_nrows * matrix.m_nrows; ++i) {
    scaled.m_data[i] = matrix.m_data[i] * scalar;
  }
  return scaled;
}

SquareMatrix operator*(double scalar, const SquareMatrix &matrix) {
  return matrix * scalar;
}

ostream &operator<<(ostream &os, const SquareMatrix &matrix) {
  for (size_t i = 0; i < matrix.m_nrows * matrix.m_nrows; ++i) {
    os << matrix.m_data[i] << " ";
  }
  return os;
}
