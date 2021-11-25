cmake_minimum_required(VERSION 3.20)

project(coursera_red)

set(CMAKE_CXX_STANDARD 23)

set(MY_SOURCE week_1/max_element_if.cpp)

include_directories(test_runner)

link_directories(test_runner)

add_subdirectory(test_runner)

add_executable(${PROJECT_NAME} ${MY_SOURCE})

target_link_libraries(${PROJECT_NAME} tester)
