cmake_minimum_required(VERSION 3.20)

project(tester)

set(CMAKE_CXX_STANDARD 23)

add_library(tester test_runner_portable.h test_runner_portable.cpp)
