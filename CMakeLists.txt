cmake_minimum_required(VERSION 3.20)

project(coursera_red)

set(CMAKE_CXX_STANDARD 23)





include_directories(profile)



include_directories(test_runner_lib)

add_subdirectory(test_runner_lib)





# set(SOURCE week_1/max_element_if.cpp)
# set(SOURCE week_1/log.cpp)
# set(SOURCE week_1/sort_by.cpp)
# set(SOURCE week_1/update_field.cpp)
# set(SOURCE week_1/bad_macro.cpp)
# set(SOURCE week_1/uniq_id.cpp)
# set(SOURCE week_1/table.cpp)
# set(SOURCE week_1/paginator.cpp)

# set(SOURCE week_2/sort_students.cpp)
# set(SOURCE week_2/learner.cpp)
# set(SOURCE week_2/expresses.cpp)
# set(SOURCE week_2/ebook.cpp)
# set(SOURCE week_2/booking.cpp)

# set(SOURCE week_3/object_pool.cpp)
# set(SOURCE week_3/swap_sort_copy.cpp)
# set(SOURCE week_3/simple_vector.cpp)
set(SOURCE week_3/linked_list.cpp)





add_executable(${PROJECT_NAME} ${SOURCE})



target_link_libraries(${PROJECT_NAME} test_runner_lib)
