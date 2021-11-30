cmake_minimum_required(VERSION 3.20)

project(coursera_red)

set(CMAKE_CXX_STANDARD 23)



#set(SOURCE week_1/max_element_if.cpp)

set(SOURCE week_1/log.cpp)



include_directories(test_runner_lib)

add_subdirectory(test_runner_lib)



add_executable(${PROJECT_NAME} ${SOURCE})



target_link_libraries(${PROJECT_NAME} test_runner_lib)
