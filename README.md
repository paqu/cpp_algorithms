# Algorithm Kata Library

A comprehensive C++17 algorithms and data structures library created as a programming kata practice. This library implements fundamental computer science concepts with modern C++ best practices, serving as both a learning resource and a production-ready toolkit.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.16+-green.svg)](https://cmake.org/)

## 🎯 Project Philosophy

This library is built following the **kata programming** approach - implementing algorithms and data structures from scratch to deepen understanding of computer science fundamentals. Each component is:

- **Pedagogically Designed**: Clear, readable implementations that teach concepts
- **Generic & Flexible**: Template-based design for maximum reusability
- **Incrementally Built**: Growing collection through continuous practice

## 🚀 Current State

### ✅ Implemented Algorithms

**Sorting Algorithms:**
- **Quick Sort** - Fully implemented with comprehensive tests
- **Insertion Sort** - Fully implemented with comprehensive tests
### 🚧 In Progress

**Sorting Algorithms (Headers declared, implementations pending):**
- Heap Sort - O(n log n), not stable
- Insertion Sort - O(n²), stable
- Merge Sort - O(n log n), stable  
- Selection Sort - O(n²), not stable

### 📋 Planned Features

- Searching algorithms (binary search, linear search)
- Data structures (linked lists, trees, hash tables)
- Graph algorithms (BFS, DFS, shortest path)
- Dynamic programming solutions
- String algorithms
- Mathematical algorithms

## 📖 Usage Examples

### Basic Sorting

```cpp
#include <algorithms/sorting/quick_sort.hpp>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    
    // Sort in ascending order
    auto sorted_asc = algorithms::sorting::quick_sort(numbers);
    
    // Sort in descending order
    auto sorted_desc = algorithms::sorting::quick_sort(numbers, std::greater<int>{});
    
    // Sort strings alphabetically
    std::vector<std::string> words = {"banana", "apple", "cherry"};
    auto sorted_words = algorithms::sorting::quick_sort(words);
    
    return 0;
}
```

### Custom Comparators

```cpp
#include <algorithms/sorting/quick_sort.hpp>

struct Person {
    std::string name;
    int age;
    double salary;
};

int main() {
    std::vector<Person> people = {
        {"Alice", 30, 70000.0},
        {"Bob", 25, 50000.0},
        {"Charlie", 35, 80000.0}
    };
    
    // Sort by age
    auto by_age = algorithms::sorting::quick_sort(people, 
        [](const Person& a, const Person& b) { 
            return a.age < b.age; 
        });
    
    // Sort by salary (highest first)
    auto by_salary = algorithms::sorting::quick_sort(people,
        [](const Person& a, const Person& b) { 
            return a.salary > b.salary; 
        });
    
    return 0;
}
```

## 🔧 Prerequisites

- **C++17 compatible compiler:**
  - GCC 7.0+ 
  - Clang 5.0+
  - MSVC 2017+ (Visual Studio 15.0+)
- **CMake 3.16+**
- **Google Test** (automatically fetched during build for testing)

## 🛠️ Installation & Build

### Clone the Repository

```bash
git clone <repository-url> <name>
cd <name>
```

### Build the Library

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Or with specific options
cmake -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON -DBUILD_BENCHMARKS=ON ..
cmake --build .
```

### Build Options

- `BUILD_TESTS` (default: ON) - Build unit tests
- `BUILD_EXAMPLES` (default: ON) - Build example programs  
- `BUILD_BENCHMARKS` (default: ON) - Build benchmark suite (not used for current state)

### Using in Your Project

#### As a Subdirectory

```cmake
add_subdirectory(path/to/algorithm-library)
target_link_libraries(your_target PRIVATE Algorithms)
```

#### Header-Only Usage

Simply include the headers you need:

```cpp
#include <algorithms/sorting/quick_sort.hpp>
// Use algorithms::sorting::quick_sort()
```

## 🧪 Testing

### Run All Tests

```bash
# From build directory
ctest

# Or run the test executable directly
./test_sort

# For verbose output
ctest --verbose
```

## 🤝 Contributing

This is a learning-focused project, and contributions are welcome! Whether you're a beginner looking to practice or an expert wanting to help, there are many ways to contribute.

### Ways to Contribute

1. **Implement Missing Algorithms**
   - Complete the declared but unimplemented sorting algorithms
   - Add new algorithm categories (searching, graph algorithms, etc.)

2. **Improve Documentation**
   - Add more usage examples
   - Improve code comments and documentation
   - Create tutorials or learning guides

3. **Testing & Quality**
   - Add more test cases
   - Implement benchmarking suite
   - Performance optimizations

4. **Code Quality**
   - Refactor for better readability
   - Add static analysis tools
   - Improve CMake configuration

### Development Setup

```bash
# Fork and clone the repository
git clone <repo_url> <name>
cd <name>

# Create a feature branch
git checkout -b feature/your-algorithm-name

# Build with all options
mkdir build && cd build
cmake -DBUILD_TESTS=ON -DBUILD_EXAMPLES=ON ..
cmake --build .

# Run tests to ensure everything works
ctest

# Make your changes, add tests, and submit a PR!
```

### Contribution Guidelines

- **Follow the existing code style** and naming conventions
- **Write comprehensive tests** for any new algorithms
- **Include usage examples** in the examples/ directory
- **Update documentation** as needed
- **Keep implementations pedagogically clear** - prefer readability over micro-optimizations
- **Use modern C++17 features** appropriately

### Algorithm Implementation Template

When adding a new algorithm, follow this structure:

```cpp
// include/algorithms/category/algorithm_name.hpp
#pragma once
#include <functional>
#include <vector>

namespace algorithms::category {

/**
 * Algorithm Name
 * Time: O(?), Space: O(?)
 * Stable/Not stable
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> algorithmName(const std::vector<T>& arr, Compare comp = Compare{});

} // namespace algorithms::category
```

## 📈 Development Roadmap

### Phase 1: Core Sorting (Current)
- ✅ Quick Sort implementation
- 🚧 Complete remaining sorting algorithms
- 🚧 Benchmarking framework

### Phase 2: Searching & Basic Data Structures
- Binary search variants
- Linear search
- Basic linked list implementation
- Stack and queue implementations

### Phase 3: Advanced Data Structures
- Binary search trees
- Hash tables
- Heaps and priority queues
- Graph representations

### Phase 4: Advanced Algorithms
- Graph traversal (BFS, DFS)
- Shortest path algorithms
- Dynamic programming classics
- String matching algorithms

## 📜 License

MIT License - see [LICENSE](LICENSE) for details.

---

_"The best way to learn algorithms is to implement them yourself."_ - This library embodies that philosophy.

**Happy Coding!** 🚀
