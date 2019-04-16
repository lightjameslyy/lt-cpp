#define BOOST_TEST_MODULE dataset_example_zip
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

int sample1[] = {1, 2};
char const* sample2[] = {"qwerty", "asdfg"};

BOOST_DATA_TEST_CASE(
    test1,
    data::make(sample1) ^ sample2,
    int_val,
    str_val) {
    std::cout << int_val << ", " << str_val << std::endl;
}

// if one of the dataset is of size 1 (singleton) or of infinite size,
// the resulting size is governed by the other dataset.

int sample3[] = {1};
char const* sample4[] = {"qwerty", "asdfg", "hello"};

BOOST_DATA_TEST_CASE(
    test2,
    data::make(sample3) ^ sample4,
    int_val,
    str_val) {
    std::cout << int_val << ", " << str_val << std::endl;
}
