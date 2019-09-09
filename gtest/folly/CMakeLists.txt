cmake_minimum_required(VERSION 3.0)

project(test_folly)

set(CMAKE_CXX_STANDARD 14)

set(FOLLY_LIBS folly gtest gtest_main pthread glog dl double-conversion iberty unwind)

add_executable(ConcurrentHashMapTest.exe ConcurrentHashMapTest.cpp)
target_link_libraries(ConcurrentHashMapTest.exe ${FOLLY_LIBS})

add_executable(FormatTest.exe FormatTest.cpp)
target_link_libraries(FormatTest.exe ${FOLLY_LIBS})

