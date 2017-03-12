#include "Unit.h"

int main() {

#pragma omp parallel for
  for(int i = 0; i < 10000; ++i) {
    Wavelength w;
  }
}
