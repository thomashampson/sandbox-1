#include <boost/mpl/apply.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/static_assert.hpp>

using namespace boost::mpl;

typedef vector_c<int, 1, 2, 3> numbers;
typedef lambda<plus<_1, int_<1> > >::type add_one;
typedef transform<numbers, add_one::apply<_1>>::type result;

typedef vector_c<int, 2, 3, 4> expected_result;

BOOST_STATIC_ASSERT(( equal<expected_result, result>::value ));
