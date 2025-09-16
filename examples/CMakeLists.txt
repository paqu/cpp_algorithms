# File: examples/CMakeLists.txt

# Basic usage
add_executable(basic_usage basic_usage.cpp)
target_link_libraries(basic_usage PRIVATE Algorithms)

# custom usage
add_executable(custom custom.cpp)
target_link_libraries(custom PRIVATE Algorithms)

