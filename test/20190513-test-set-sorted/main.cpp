#define BOOST_TEST_MODULE Map To Pointer Test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <set>
#include <iostream>
#include <climits>

BOOST_AUTO_TEST_CASE(map_to_pointer) {
    std::set<int> myset;
    std::set<int>::iterator it;

    //insert some values:
    myset.insert(1);
    myset.insert(41);
    myset.insert(234);
    myset.insert(983);
    myset.insert(2);

    // show content:
    int prev = INT_MIN;
    for (it=myset.begin(); it!=myset.end(); ++it) {
        BOOST_TEST((prev <= *it));
        std::cout << *it << '\n';
        prev = *it;
    }
}
