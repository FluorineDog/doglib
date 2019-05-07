# include(GoogleTest)
enable_testing()
include(GoogleTest)
add_subdirectory("/usr/src/gtest" gtest.out)
# find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})

dog_test(common)
dog_test(union_find)

add_subdirectory(graph)
add_subdirectory(math)