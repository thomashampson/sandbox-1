/**
 * Implement a ternary-metafunction to take a compound type C(x,Y) and
 * replace each occurence of X with Y.
 *
 * Examples:
 *   - replace_type<void *, void, int>::type t1 // ->int*
 *   - replace_type<int const*[10], int const, long>::type t2 // -> long*[10]
 *   - replace_type<(char&)(*)(char&), char&, long&>::type t3 // ->
 *(long&)(*)(long&)
 */
#include <type_traits>

/**
 * Generic case has no type parameter. Results in a compilation error
 * if used for a fundamental type or a compound type not considered here.
*/
template <typename C, typename X, typename Y> struct replace_type {};

/**
  * Forward declare type to return appropriate type depending on
  * 
  */
template <typename C, typename X, typename Y, bool is_same>
struct replace_type_check {};

/**
 * Specialization if type(C)=type(X) to "return" Y
 */
template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, true> {
  typedef Y type;
};

/**
 * Specialization for type(C)!=type(X) to call the outer
 * replace_type_dispatch on C to anaylyse any possible qualifiers
 */
template <typename C, typename X, typename Y>
struct replace_type_dispatch<C, X, Y, false> {
  typedef replace_type<C, X, Y>
};

/**
 * Specialization for pointer types
 * C is now the pointee type. If it is the same as X then it is replaced
 * with Y and the pointer type is added back, else C* will be "returned"
 */
template <typename C, typename X, typename Y> struct replace_type<C *, X, Y> {
  typedef typename std::add_pointer<
      typename detail::replace_type_impl<C, X, Y>::type>::type type;
};
/**
 * Specialization for reference types
 * C is now the referencee type. If it is the same as X then it is replaced
 * with Y and the referencee type is added back, else C* will be "returned"
 */
template <typename C, typename X, typename Y> struct replace_type<C &, X, Y> {
  typedef typename std::add_lvalue_reference<
      typename detail::replace_type_impl<C, X, Y>::type>::type type;
};

/**
 * Specialization for C-array types
 * C is now the element type. If it is the same as X then it is replaced
 * with Y and the array type is added back, else C[N] will be "returned"
 */
template <typename C, size_t N, typename X, typename Y>
struct replace_type<C[N], X, Y> {
  typedef typename replace_type<C, X, Y>::type type[N];
};

/**
 * Specialization for function pointers
 * C is now the element type. If it is the same as X then it is replaced
 * with Y and the array type is added back, else C[N] will be "returned"
 */
template <typename R, typename Arg1, typename X, typename Y>
struct replace_type<R (*)(Arg1), X, Y> {
  typedef typename replace_type<R, X, Y>::type return_type;
  //  typedef typename replace_type<Arg1, X, Y>::type argument_type;

  //    typedef return_type (*type)(argument_type);
  // typedef R type;
};

int main() {
  static_assert(
      std::is_same<replace_type<void *, void, int>::type, int *>::value,
      "Expected result type to be 'int*'");
  static_assert(
      std::is_same<replace_type<int const * [10], int const, long>::type,
                   long * [10]>::value,
      "Expected result type to be 'long * [10]'");
  //  static_assert(
  //      std::is_same<replace_type<char &(*)(char &), char &, long &>::type,
  //                   long &(*)(long &)>::value,
  //      "Expected result type to be '(long&)(*)(long&)'");

  int status;
  const char *realname;
  using result_type = replace_type<char &, char &, long &>::type;
  realname = abi::__cxa_demangle(typeid(char &).name(), 0, 0, &status);
  std::cerr << realname << "\n";
}
