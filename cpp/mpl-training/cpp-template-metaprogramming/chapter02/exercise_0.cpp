/**
 * Example of a unary metafunction to add a const reference qualifier
 */
#include <type_traits>

namespace detail {
  // Primary template for general case
  // Nested ::type adds const&
  template <typename T, bool is_reference>
  struct add_const_ref_impl {
    typedef T const& type;
  };
  // Specialization for reference types
  // Nested type returns the original type
  template <typename T>
  struct add_const_ref_impl<T, true> {
    typedef T type;
  };
}

// Provides the add_const_ref metafunction
// in the general case
template<typename T>
struct add_const_ref : detail::add_const_ref_impl<T, false> {
};
// Provides the add_const_ref metafunction
// for non-const reference types
template<typename T>
struct add_const_ref<T&> :
  detail::add_const_ref_impl<T&, true> {
};
// Provides the add_const_ref metafunction
// for const reference types
template<typename T>
struct add_const_ref<const T&> :
  detail::add_const_ref_impl<const T&, true> {
};


// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------
struct A {
};

int main() {
  static_assert(std::is_same<add_const_ref<A>::type, const A&>::value,
                "Result is expected to be const A &");
  static_assert(std::is_same<add_const_ref<A const&>::type, const A&>::value,
                "Result is expected to be const A&");
  static_assert(std::is_same<add_const_ref<A&>::type,  A&>::value,
                "Result is expected to be A&");

}
