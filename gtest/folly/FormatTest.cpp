#include <string>
#include <iostream>
#include <cstdint>

#include <folly/Format.h>

#include <gtest/gtest.h>

TEST(FormatTest, format) {
    std::string str = folly::format("The answers are {} and {}", 23, 42).str();
    std::cout << str << std::endl;
    ASSERT_EQ(str, "The answers are 23 and 42");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
