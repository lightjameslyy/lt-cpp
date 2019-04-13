#define BOOST_TEST_MODULE dataset_example
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <sstream>

namespace bdata = boost::unit_test::data;

// Dataset generating a Fibonacii sequence
class fibonacii_dataset {
  public:
    // Sample type is int
    using sample=int;
    enum { arity = 1 };

    struct iterator {
        iterator() : a(1), b(1) {}

        int operator*() const {
            return b;
        }
        void operator++() {
            a = a+b;
            std::swap(a, b);
        }
      private:
        int a;
        int b; // b is the output
    };

    fibonacii_dataset() {}

    // size is infinite
    bdata::size_t size() const {
        return bdata::BOOST_TEST_DS_INFINITE_SIZE;
    }

    // iterator
    iterator begin() const {
        return iterator();
    }

};

// Registering fibonacii_dataset as a proper dataset
namespace boost {
namespace unit_test {
namespace data {
namespace monomorphic {
template <>
struct is_dataset<fibonacii_dataset> : boost::mpl::true_ {};
}
}
}
}

// Creating a test-driven dataset
BOOST_DATA_TEST_CASE(
    test1,
    fibonacii_dataset() ^ bdata::make( {1, 2, 3, 5, 8, 13, 21, 35, 56}),
    fib_sample, exp) {
    BOOST_TEST(fib_sample == exp);
}
