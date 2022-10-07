cmake_minimum_required(VERSION 3.24)
project(coursera_red)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -pthread)





include_directories(test_runner_lib profile)
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
# set(SOURCE week_3/linked_list.cpp)

# set(SOURCE week_4/string_set.cpp)
# set(SOURCE week_4/athlets.cpp)
# set(SOURCE week_4/stack_vector.cpp)
# set(SOURCE week_4/translator.cpp)
# set(SOURCE week_4/airport_counter.cpp)
# set(SOURCE week_4/text_editor.cpp)

# file(GLOB SOURCE
#     week_4/server_stats.cpp
#     week_4/http_request.h
#     week_4/stats.h
#     week_4/stats.cpp)

# set(SOURCE week_5/josephus_permutation.cpp)
# set(SOURCE week_5/group_heavy_strings.cpp)
# set(SOURCE week_5/simple_vector_copy_assignment.cpp)
# set(SOURCE week_5/split_into_sentences.cpp)
# set(SOURCE week_5/simple_vector_2.cpp)
# set(SOURCE week_5/merge_sort_3.cpp)
# set(SOURCE week_5/priority_collection_2.cpp)

# set(SOURCE week_5/async.cpp)
# set(SOURCE week_5/matrix_sum.cpp)
# set(SOURCE week_5/explore_key_words.cpp)
# set(SOURCE week_5/synchronized.cpp)
# set(SOURCE week_5/concurrent_map.cpp)

# set(SOURCE week_5/boost_check.cpp)

# file(GLOB SOURCE project/*)

file(GLOB SOURCE project_multi/*)





add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} test_runner_lib)





# # # # # # for c compiler
# set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
# # # # # # for c++
# SET(CMAKE_CXX_FLAGS -pthread)
