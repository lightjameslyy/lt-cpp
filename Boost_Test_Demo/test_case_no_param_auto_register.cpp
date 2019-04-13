#define BOOST_TEST_MODULE example
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

/* Compare with void free_test_function() */
BOOST_AUTO_TEST_CASE( free_test_function ) {
    BOOST_TEST( true /* test assertion */ );
}
