cmake_minimum_required(VERSION 3.0)

project(test_folly)

add_executable(ConcurrentHashMapTest.exe ConcurrentHashMapTest.cpp)
target_link_libraries(ConcurrentHashMapTest.exe gtest gtest_main folly pthread glog dl double-conversion iberty)

