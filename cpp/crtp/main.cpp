#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

/**
 * Mixin to add scalable operations to
 * class supporting an iterator-style
 * interface.
 */
template<typename Derived>
class Scalable {
public:
  void operator*=(const double scale) {
    Derived & self = static_cast<Derived&>(*this);
    std::transform(std::begin(self), std::end(self),
                   std::begin(self),
                   [scale](const double &x){return x*scale;});
  }
};

template<typename T>
class ScaleableVector : public std::vector<T>,
                        public Scalable<ScaleableVector<T>> {
public:
  // inherit constructors
  using std::vector<T>::vector;
};

int main() {
  ScaleableVector<double> x({1., 2., 3., 4., 5.});
  x *= 2.;
  std::copy(std::begin(x), std::end(x),
            std::ostream_iterator<double>(std::cerr, ","));
  std::cerr << "\n";

}
