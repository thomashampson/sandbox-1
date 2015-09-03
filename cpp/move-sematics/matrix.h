#ifndef MATRIX_H_
#define MATRIX_H_

#include <iosfwd>

class SquareMatrix {
public:
  SquareMatrix(size_t nrows);
  ~SquareMatrix();
  // Copy constructor
  SquareMatrix(const SquareMatrix & other);
  // Copy assignment operator
  SquareMatrix& operator=(const SquareMatrix & rhs);
  // Move constructor
  SquareMatrix(SquareMatrix && rhs);
  // Move assignment operator
  SquareMatrix& operator=(SquareMatrix && rhs);

private:
  friend SquareMatrix operator*(const SquareMatrix& matrix, double scalar);
  friend SquareMatrix operator*(double scalar, const SquareMatrix& matrix);
  friend std::ostream & operator<<(std::ostream &, const SquareMatrix &);

  double * allocate(const size_t nrows);

  double *m_data;
  size_t m_nrows;
};

#endif // MATRIX_H_
