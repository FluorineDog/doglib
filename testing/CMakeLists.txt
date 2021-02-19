# include(GoogleTest)
enable_testing()
include(GoogleTest)
# find_package(GTest)
include_directories(${GTEST_INCLUDE_DIR})

dog_test(common)
dog_test(union_find)
dog_test(time)

add_subdirectory(graph)
add_subdirectory(math)
