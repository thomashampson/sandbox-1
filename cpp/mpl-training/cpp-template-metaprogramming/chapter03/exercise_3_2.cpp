#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>

using namespace boost::mpl;

// Simple metafunction class

// Without placeholder support
// struct square {
//   template <class T>
//   struct apply {
//     typedef typename times<T, T>::type type;
//   };
// };

// Using mpl::lambda for placeholder support
template <class T>
struct square
  : lambda<typename times<T, T>::type> {};

typedef vector_c<int, 1, 2, 3> numbers;
typedef transform<numbers, square<_1>>::type result;

typedef vector_c<int, 1, 4, 9> expected_result;
BOOST_STATIC_ASSERT(( equal<expected_result, result>::value ));
