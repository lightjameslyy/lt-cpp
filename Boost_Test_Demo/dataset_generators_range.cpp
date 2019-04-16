#define BOOST_TEST_MODULE dataset_generators_range
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

BOOST_DATA_TEST_CASE(
    test1,
    data::xrange(5)) {
    std::cout << "test 1: " << sample << std::endl;
    BOOST_TEST((sample <= 4 && sample >=0));
}

BOOST_DATA_TEST_CASE(
    test2,
    data::xrange<int>((data::begin=1, data::end=10, data::step=3))) {
    std::cout << "test 2: " << sample << std::endl;
    BOOST_TEST((sample <= 4 && sample >=0));
}

