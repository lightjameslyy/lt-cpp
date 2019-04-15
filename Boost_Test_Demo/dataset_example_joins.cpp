#define BOOST_TEST_MODULE dataset_example_join
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

int sample1[] = {1, 2};
int sample2[] = {8, 9, 10};

BOOST_DATA_TEST_CASE(
    test1,
    data::make(sample1) + sample2,
    var) {
    std::cout << var << std::endl;
}

