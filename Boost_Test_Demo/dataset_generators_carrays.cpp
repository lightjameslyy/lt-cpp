#define BOOST_TEST_MODULE dataset_generators_carrays
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

const char* arr[] = {"cat", "dog"};

BOOST_DATA_TEST_CASE(
    test1,
    data::xrange(2) ^ data::make(arr),
    xr, arr_elem) {
    std::cout << "test 1: "
              << xr << ", "
              << arr_elem
              << std::endl;
    BOOST_TEST(arr_elem != "mammoth");
}

