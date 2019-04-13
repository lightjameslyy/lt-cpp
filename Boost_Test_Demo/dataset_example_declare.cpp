#define BOOST_TEST_MODULE dataset_example
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

BOOST_DATA_TEST_CASE(test_case_arity1_implicit, data::xrange(5)) {
    BOOST_TEST((sample <= 4 && sample >= 0));
}

BOOST_DATA_TEST_CASE( test_case_arity1, data::xrange(5), my_var ) {
    BOOST_TEST((my_var <= 4 && my_var >= 0));
}

BOOST_DATA_TEST_CASE( test_case_arity2, data::xrange(6, 11) ^ data::xrange(5), apples, potatoes) {
    std::cout << apples << " " << potatoes << std::endl;
    BOOST_TEST((apples <= 10 && apples >= 6));
    BOOST_TEST((potatoes <= 4 && potatoes >= 0));
}
