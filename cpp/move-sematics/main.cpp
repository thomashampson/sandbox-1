#include "matrix.h"
#include <iostream>

using namespace std;

SquareMatrix create(size_t nrows) {
  SquareMatrix s(nrows);
  return s;
}

SquareMatrix createComplex(size_t nrows, double x) {
  if(x > 1.0) {
    SquareMatrix s1(nrows);
    return s1;
  } else {
    SquareMatrix s2(nrows);
    return s2;
  }
}

int main() {
  cerr << "------ construct & assign from return value ----\n";
  SquareMatrix m1(3);
  m1 = create(2);
  cerr << "------ construct from return value (simple) ----\n";
  SquareMatrix m2(create(2));
  cerr << "------ construct from return value (complex) ----\n";
  SquareMatrix m3(createComplex(3, 1.1));
  cerr << "------ construct from temporary ----\n";
  SquareMatrix m4(create(2)*2);
  cerr << "-----------------------------\n";
}
