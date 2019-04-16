#define BOOST_TEST_MODULE dataset_generators_random
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <iostream>

namespace data = boost::unit_test::data;

BOOST_DATA_TEST_CASE(
    test1,
    data::random(1, 17) ^ data::xrange(7),
    random_sample, index) {
    std::cout << "test 1: " << random_sample
              << ", " << index << std::endl;
    BOOST_TEST((random_sample <= 17 && random_sample >=1));
}

BOOST_DATA_TEST_CASE(
    test2,
    data::random( (data::distribution=std::uniform_real_distribution<float>(1, 2)) )
    ^ data::xrange(7),
    random_sample, index ) {
    std::cout << "test 2: " << random_sample
              << ", " << index << std::endl;
    BOOST_TEST(random_sample < 1.7); // 30% chance of failure
}
