#include <iostream>
#include <type_traits>

template <typename T>
void do_stuff(const T&,
              std::enable_if_t<std::is_integral<T>::value, T>* = nullptr) {
  std::cerr << "Integral types\n";
}

template <typename T>
void do_stuff(const T&,
              std::enable_if_t<std::is_class<T>::value, T>* = nullptr) {
     std::cerr << "Class types\n";}

struct A {};

int main() {
  do_stuff(1);
  do_stuff(A());
}
