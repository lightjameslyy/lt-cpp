#define BOOST_TEST_MODULE dataset_example_grid
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

BOOST_DATA_TEST_CASE(
    test1,
    data::xrange(2) * data::xrange(3),
    xr1, xr2) {
    std::cout << "test 1: " << xr1 << ", " << xr2 << std::endl;
    BOOST_TEST((xr1 <= 2 && xr2 <= 3));
}

BOOST_DATA_TEST_CASE(
    test2,
    data::xrange(3)
    *
    ( data::random(
          data::distribution=std::uniform_real_distribution<float>(1, 2))
      ^ data::xrange(2)
    ),
    xr, random_sample, index) {
    std::cout << "test 2: "
              << xr << " / "
              << random_sample << ", " << index
              << std::endl;
    BOOST_TEST(random_sample < 1.7); // 30% chance of failure
}

