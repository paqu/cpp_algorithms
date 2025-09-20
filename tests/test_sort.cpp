#include <algorithm>
#include <algorithms/sorting/insertion_sort.hpp>
#include <algorithms/sorting/merge_sort.hpp>
#include <algorithms/sorting/quick_sort.hpp>
#include <algorithms/sorting/selection_sort.hpp>
// #include <algorithms/sorting/heap_sort.hpp>      // Add when implemented
#include <functional>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace {

// Generic comparator type alias: accepts two const T& and returns bool
template <typename T>
using Comparator = std::function<bool(const T &, const T &)>;

// Sort function type: takes a vector<T> and a comparator, returns a vector<T>
template <typename T>
using SortFunction =
    std::function<std::vector<T>(const std::vector<T> &, Comparator<T>)>;

// Enum for algorithm identification (for better test reporting)
enum class SortAlgorithm {
    QuickSort,
    InsertionSort,
    MergeSort,
    SelectionSort,
    // HeapSort       // Add when implemented
};

// Convert enum to string for test names
std::string AlgorithmName(SortAlgorithm algo) {
    switch (algo) {
    case SortAlgorithm::QuickSort:
        return "QuickSort";
    case SortAlgorithm::InsertionSort:
        return "InsertionSort";
    case SortAlgorithm::MergeSort:
        return "MergeSort";
    case SortAlgorithm::SelectionSort:
        return "SelectionSort";
    // case SortAlgorithm::HeapSort: return "HeapSort";
    default:
        return "Unknown";
    }
}

// Test parameter structure
struct SortTestParam {
    SortAlgorithm algorithm;
    SortFunction<int> sort_func;

    // Constructor for integer sorting functions
    SortTestParam(SortAlgorithm algo, SortFunction<int> func)
        : algorithm(algo), sort_func(func) {}
};

// Custom test name generator
struct SortTestParamName {
    template <typename ParamType>
    std::string
    operator()(const ::testing::TestParamInfo<ParamType> &info) const {
        return AlgorithmName(info.param.algorithm);
    }
};

class SortAlgorithmTest : public ::testing::TestWithParam<SortTestParam> {
  protected:
    void SetUp() override {
        sort_func = GetParam().sort_func;
        algorithm_name = AlgorithmName(GetParam().algorithm);
    }

    SortFunction<int> sort_func;
    std::string algorithm_name;
};

// ============================================================================
// SHARED TEST CASES - These run for ALL algorithms
// ============================================================================

TEST_P(SortAlgorithmTest, BasicIntegerSorting) {
    std::vector<int> input = {5, 2, 8, 1, 9, 3};
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};

    auto result = sort_func(input, std::less<int>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, EmptyVector) {
    std::vector<int> empty;
    auto result = sort_func(empty, std::less<int>{});

    EXPECT_TRUE(result.empty()) << "Failed for " << algorithm_name;
    EXPECT_EQ(result.size(), 0) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, SingleElement) {
    std::vector<int> single = {42};
    auto result = sort_func(single, std::less<int>{});

    ASSERT_EQ(result.size(), 1) << "Failed for " << algorithm_name;
    EXPECT_EQ(result[0], 42) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, AlreadySorted) {
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    auto result = sort_func(sorted, std::less<int>{});

    EXPECT_EQ(result, sorted) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, ReverseSorted) {
    std::vector<int> reverse = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    auto result = sort_func(reverse, std::less<int>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, WithDuplicates) {
    std::vector<int> with_dups = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    auto result = sort_func(with_dups, std::less<int>{});

    // Check if sorted
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()))
        << "Failed for " << algorithm_name;

    // Check if all elements are preserved
    std::vector<int> original_sorted = with_dups;
    std::sort(original_sorted.begin(), original_sorted.end());
    EXPECT_EQ(result, original_sorted) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, DescendingOrder) {
    std::vector<int> input = {5, 2, 8, 1, 9, 3};
    std::vector<int> expected = {9, 8, 5, 3, 2, 1};

    auto result = sort_func(input, std::greater<int>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, AllSameElements) {
    std::vector<int> same = {7, 7, 7, 7, 7};
    auto result = sort_func(same, std::less<int>{});

    EXPECT_EQ(result.size(), 5) << "Failed for " << algorithm_name;
    for (int val : result) {
        EXPECT_EQ(val, 7) << "Failed for " << algorithm_name;
    }
}

TEST_P(SortAlgorithmTest, TwoElements) {
    std::vector<int> two = {5, 2};
    std::vector<int> expected = {2, 5};

    auto result = sort_func(two, std::less<int>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

TEST_P(SortAlgorithmTest, NegativeNumbers) {
    std::vector<int> negatives = {-5, 3, -1, 0, -10, 7, -3};
    std::vector<int> expected = {-10, -5, -3, -1, 0, 3, 7};

    auto result = sort_func(negatives, std::less<int>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

// Algorithm-specific dataset sizes (different algorithms have different
// performance characteristics)
TEST_P(SortAlgorithmTest, ModerateDataset) {
    // Use smaller dataset for O(n²) algorithms, larger for O(n log n)
    size_t dataset_size;
    switch (GetParam().algorithm) {
    case SortAlgorithm::InsertionSort:
        dataset_size = 100; // Smaller for O(n²) algorithms
        break;
    case SortAlgorithm::QuickSort:
        dataset_size = 1000; // Larger for O(n log n) algorithms
        break;
    default:
        dataset_size = 500; // Default moderate size
    }

    // Generate reverse sorted dataset
    std::vector<int> data;
    for (size_t i = dataset_size; i >= 1; i--) {
        data.push_back(static_cast<int>(i));
    }

    auto result = sort_func(data, std::less<int>{});

    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()))
        << "Failed for " << algorithm_name;
    EXPECT_EQ(result.size(), dataset_size) << "Failed for " << algorithm_name;
    EXPECT_EQ(result.front(), 1) << "Failed for " << algorithm_name;
    EXPECT_EQ(result.back(), static_cast<int>(dataset_size))
        << "Failed for " << algorithm_name;
}

// ============================================================================
// PARAMETERIZED TEST INSTANTIATION
// ============================================================================

INSTANTIATE_TEST_SUITE_P(
    AllSortingAlgorithms, SortAlgorithmTest,
    ::testing::Values(
        SortTestParam{SortAlgorithm::QuickSort,
                      [](const std::vector<int> &v, auto comp) {
                          return algorithms::sorting::quick_sort(v, comp);
                      }},
        SortTestParam{SortAlgorithm::InsertionSort,
                      [](const std::vector<int> &v, auto comp) {
                          return algorithms::sorting::insertion_sort(v, comp);
                      }},
        SortTestParam{SortAlgorithm::MergeSort,
                      [](const std::vector<int> &v, auto comp) {
                          return algorithms::sorting::merge_sort(v, comp);
                      }},
        SortTestParam{SortAlgorithm::SelectionSort,
                      [](const std::vector<int> &v, auto comp) {
                          return algorithms::sorting::selection_sort(v, comp);
                      }}),
    SortTestParamName{});

// ============================================================================
// ALGORITHM-SPECIFIC TESTS
// ============================================================================

// Specific tests that only make sense for certain algorithms
class InsertionSortSpecificTest : public ::testing::Test {};

TEST_F(InsertionSortSpecificTest, BestCasePerformance) {
    // Insertion sort is O(n) for already sorted data - this is its strength
    std::vector<int> already_sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto result = algorithms::sorting::insertion_sort(already_sorted);

    EXPECT_EQ(result, already_sorted);
    // In a real scenario, you might time this to verify O(n) performance
}

TEST_F(InsertionSortSpecificTest, SmallDatasetEfficiency) {
    // Insertion sort is often faster than advanced algorithms for small
    // datasets
    std::vector<int> small = {3, 1, 4};
    std::vector<int> expected = {1, 3, 4};

    auto result = algorithms::sorting::insertion_sort(small);
    EXPECT_EQ(result, expected);
}

class QuickSortSpecificTest : public ::testing::Test {};

TEST_F(QuickSortSpecificTest, WorstCaseHandling) {
    // Quick sort worst case is already sorted data (with naive pivot selection)
    std::vector<int> worst_case = {1, 2, 3, 4, 5};
    auto result = algorithms::sorting::quick_sort(worst_case);

    EXPECT_EQ(result, worst_case);
}

// ============================================================================
// STRING SORTING TESTS (Separate parameterized test for different types)
// ============================================================================

struct StringSortTestParam {
    SortAlgorithm algorithm;
    SortFunction<std::string> sort_func;

    StringSortTestParam(SortAlgorithm algo, SortFunction<std::string> func)
        : algorithm(algo), sort_func(func) {}
};

class StringSortTest : public ::testing::TestWithParam<StringSortTestParam> {
  protected:
    void SetUp() override {
        sort_func = GetParam().sort_func;
        algorithm_name = AlgorithmName(GetParam().algorithm);
    }

    SortFunction<std::string> sort_func;
    std::string algorithm_name;
};

TEST_P(StringSortTest, BasicStringSorting) {
    std::vector<std::string> words = {"banana", "apple", "cherry", "date"};
    std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};

    auto result = sort_func(words, std::less<std::string>{});

    EXPECT_EQ(result, expected) << "Failed for " << algorithm_name;
}

TEST_P(StringSortTest, CustomComparatorLength) {
    std::vector<std::string> words = {"cat", "elephant", "dog", "ant",
                                      "butterfly"};

    auto result =
        sort_func(words, [](const std::string &a, const std::string &b) {
            return a.length() < b.length();
        });

    // Verify sorted by length
    for (size_t i = 0; i < result.size() - 1; i++) {
        EXPECT_LE(result[i].length(), result[i + 1].length())
            << "Failed for " << algorithm_name;
    }
}

INSTANTIATE_TEST_SUITE_P(
    StringSorting, StringSortTest,
    ::testing::Values(
        StringSortTestParam{SortAlgorithm::QuickSort,
                            [](const std::vector<std::string> &v, auto comp) {
                                return algorithms::sorting::quick_sort(v, comp);
                            }},
        StringSortTestParam{SortAlgorithm::InsertionSort,
                            [](const std::vector<std::string> &v, auto comp) {
                                return algorithms::sorting::insertion_sort(
                                    v, comp);
                            }},
        StringSortTestParam{SortAlgorithm::MergeSort,
                            [](const std::vector<std::string> &v, auto comp) {
                                return algorithms::sorting::merge_sort(v, comp);
                            }},
        StringSortTestParam{SortAlgorithm::SelectionSort,
                            [](const std::vector<std::string> &v, auto comp) {
                                return algorithms::sorting::selection_sort(
                                    v, comp);
                            }}),
    SortTestParamName{});

} // anonymous namespace
