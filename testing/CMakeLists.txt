# include(GoogleTest)
enable_testing()
include(GoogleTest)
add_subdirectory("/usr/src/gtest" gtest.out)
# find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(test_common test_common.cpp)
target_link_libraries(test_common gtest_main)
gtest_discover_tests(test_common)

add_executable(test_union_find test_union_find.cpp)
target_link_libraries(test_union_find gtest_main)
gtest_discover_tests(test_union_find)

add_subdirectory(graph)
add_subdirectory(math)