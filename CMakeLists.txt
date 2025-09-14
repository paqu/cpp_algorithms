cmake_minimum_required(VERSION 3.16)

project(Algorithms 
    VERSION 1.0.0
    DESCRIPTION "Generic algorithms library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /O2")
endif()

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

# Library
add_library(Algorithms
    src/sorting/quick_sort.cpp
    src/sorting/merge_sort.cpp
    src/sorting/selection_sort.cpp
    src/sorting/insertion_sort.cpp
    src/sorting/heap_sort.cpp
)

target_include_directories(Algorithms
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(Algorithms PUBLIC cxx_std_17)

