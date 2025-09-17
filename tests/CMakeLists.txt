include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    GIT_SHALLOW    true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(test_sort test_sort.cpp)

# Link with Google Test and our library
target_link_libraries(test_sort 
    PRIVATE 
        Algorithms       
        gtest_main
        gtest
)

# Include Google Test in CTest
include(GoogleTest)
gtest_discover_tests(test_sort)
