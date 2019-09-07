cmake_minimum_required(VERSION 3.0)

#include_directories(${Project_SOURCE_DIR}/googletest-release-1.8.1/googletest/include)

#新建一个测试工程
project(test_map)
add_executable(test_map.exe test_map.cpp)
target_link_libraries(test_map.exe gtest gtest_main)

