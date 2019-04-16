#define BOOST_TEST_MODULE dataset_generators_singleton
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

BOOST_DATA_TEST_CASE(
    test1,
    data::make(2),
    singleton) {
    std::cout << "test 1: " << singleton << std::endl;
    BOOST_TEST(singleton == 2);
}

BOOST_DATA_TEST_CASE(
    test2,
    data::xrange(3) ^ data::make(2),
    xr, singleton) {
    std::cout << "test 2: " << xr << ", " << singleton << std::endl;
    BOOST_TEST(singleton == 2);
}

