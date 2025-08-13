cmake_minimum_required(VERSION 3.10)

# Removed test_split_range and test_split_range_by_clusters targets (source files deleted)

add_executable(gen_test_rootfile gen_test_rootfile.cpp)
target_link_libraries(gen_test_rootfile ${ROOT_LIBS})
target_include_directories(gen_test_rootfile PRIVATE ../include)

add_executable(test_split_range_by_clusters test_split_range_by_clusters.cpp gen_test_rootfile.cpp ../src/Utils.cpp)
target_link_libraries(test_split_range_by_clusters gtest_main ${ROOT_LIBS} WireDict)
target_include_directories(test_split_range_by_clusters PRIVATE ../include)
add_test(NAME test_split_range_by_clusters COMMAND test_split_range_by_clusters)
set_tests_properties(test_split_range_by_clusters PROPERTIES WORKING_DIRECTORY ${CMAKE_BINARY_DIR}) 