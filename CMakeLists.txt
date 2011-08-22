project(ringbuffer_test)
cmake_minimum_required(VERSION 2.6)
find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(ringbuffer_test ringbuffer_unittest.cc ringbuffer.c)
target_link_libraries(ringbuffer_test gtest gtest_main pthread)
