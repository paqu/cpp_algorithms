#include <algorithm>
#include <algorithms/sorting/quick_sort.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace {

class QuickSortTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Setup code for each test
    }

    void TearDown() override {
        // Cleanup code for each test
    }
};

// Basic functionality tests
TEST_F(QuickSortTest, BasicIntegerSorting) {
    std::vector<int> input = {5, 2, 8, 1, 9, 3};
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};

    auto result = algorithms::sorting::quick_sort(input);

    EXPECT_EQ(result, expected);
}

TEST_F(QuickSortTest, EmptyVector) {
    std::vector<int> empty;
    auto result = algorithms::sorting::quick_sort(empty);

    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0);
}

TEST_F(QuickSortTest, SingleElement) {
    std::vector<int> single = {42};
    auto result = algorithms::sorting::quick_sort(single);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 42);
}

TEST_F(QuickSortTest, AlreadySorted) {
    std::vector<int> sorted = {1, 2, 3, 4, 5};
    auto result = algorithms::sorting::quick_sort(sorted);

    EXPECT_EQ(result, sorted);
}

TEST_F(QuickSortTest, ReverseSorted) {
    std::vector<int> reverse = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    auto result = algorithms::sorting::quick_sort(reverse);

    EXPECT_EQ(result, expected);
}

TEST_F(QuickSortTest, WithDuplicates) {
    std::vector<int> with_dups = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    auto result = algorithms::sorting::quick_sort(with_dups);

    // Check if sorted
    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));

    // Check if all elements are preserved
    std::vector<int> original_sorted = with_dups;
    std::sort(original_sorted.begin(), original_sorted.end());
    EXPECT_EQ(result, original_sorted);
}

// Comparator tests
TEST_F(QuickSortTest, DescendingOrder) {
    std::vector<int> input = {5, 2, 8, 1, 9, 3};
    std::vector<int> expected = {9, 8, 5, 3, 2, 1};

    auto result = algorithms::sorting::quick_sort(input, std::greater<int>{});

    EXPECT_EQ(result, expected);
}

TEST_F(QuickSortTest, StringSorting) {
    std::vector<std::string> words = {"banana", "apple", "cherry", "date"};
    std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};

    auto result = algorithms::sorting::quick_sort(words);

    EXPECT_EQ(result, expected);
}

TEST_F(QuickSortTest, CustomComparatorLength) {
    std::vector<std::string> words = {"cat", "elephant", "dog", "ant",
                                      "butterfly"};

    auto result = algorithms::sorting::quick_sort(
        words, [](const std::string &a, const std::string &b) {
            return a.length() < b.length();
        });

    // Verify sorted by length
    for (size_t i = 0; i < result.size() - 1; i++) {
        EXPECT_LE(result[i].length(), result[i + 1].length());
    }
}

// Edge case tests
TEST_F(QuickSortTest, AllSameElements) {
    std::vector<int> same = {7, 7, 7, 7, 7};
    auto result = algorithms::sorting::quick_sort(same);

    EXPECT_EQ(result.size(), 5);
    for (int val : result) {
        EXPECT_EQ(val, 7);
    }
}

TEST_F(QuickSortTest, TwoElements) {
    std::vector<int> two = {5, 2};
    std::vector<int> expected = {2, 5};

    auto result = algorithms::sorting::quick_sort(two);

    EXPECT_EQ(result, expected);
}

TEST_F(QuickSortTest, TwoElementsReversed) {
    std::vector<int> two = {2, 5};
    std::vector<int> expected = {5, 2};

    auto result = algorithms::sorting::quick_sort(two, std::greater<int>{});

    EXPECT_EQ(result, expected);
}

// Performance and stability tests
TEST_F(QuickSortTest, LargeDataset) {
    // Generate large dataset (reverse sorted)
    std::vector<int> large_data;
    for (int i = 1000; i >= 1; i--) {
        large_data.push_back(i);
    }

    auto result = algorithms::sorting::quick_sort(large_data);

    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
    EXPECT_EQ(result.size(), 1000);
    EXPECT_EQ(result.front(), 1);
    EXPECT_EQ(result.back(), 1000);
}

TEST_F(QuickSortTest, NegativeNumbers) {
    std::vector<int> negatives = {-5, 3, -1, 0, -10, 7, -3};
    std::vector<int> expected = {-10, -5, -3, -1, 0, 3, 7};

    auto result = algorithms::sorting::quick_sort(negatives);

    EXPECT_EQ(result, expected);
}

// Type tests
TEST_F(QuickSortTest, DoubleValues) {
    std::vector<double> doubles = {3.14, 2.71, 1.41, 0.57, 2.23};
    auto result = algorithms::sorting::quick_sort(doubles);

    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));
    EXPECT_DOUBLE_EQ(result[0], 0.57);
    EXPECT_DOUBLE_EQ(result.back(), 3.14);
}

// Custom type test
struct Person {
    std::string name;
    int age;

    bool operator==(const Person &other) const {
        return name == other.name && age == other.age;
    }
};

TEST_F(QuickSortTest, CustomStructSorting) {
    std::vector<Person> people = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}, {"Diana", 28}};

    auto result = algorithms::sorting::quick_sort(
        people, [](const Person &a, const Person &b) { return a.age < b.age; });

    ASSERT_EQ(result.size(), 4);
    EXPECT_EQ(result[0].name, "Bob");
    EXPECT_EQ(result[0].age, 25);
    EXPECT_EQ(result[3].name, "Charlie");
    EXPECT_EQ(result[3].age, 35);
}

// Parameterized tests for different data types
class QuickSortTypeTest : public ::testing::TestWithParam<std::vector<int>> {};

TEST_P(QuickSortTypeTest, SortsCorrectly) {
    auto input = GetParam();
    auto result = algorithms::sorting::quick_sort(input);

    EXPECT_TRUE(std::is_sorted(result.begin(), result.end()));

    // Verify same elements (count each element)
    std::sort(input.begin(), input.end());
    EXPECT_EQ(result, input);
}

INSTANTIATE_TEST_SUITE_P(
    DifferentInputs, QuickSortTypeTest,
    ::testing::Values(std::vector<int>{},              // empty
                      std::vector<int>{1},             // single
                      std::vector<int>{2, 1},          // two elements
                      std::vector<int>{3, 3, 3},       // all same
                      std::vector<int>{1, 2, 3, 4, 5}, // sorted
                      std::vector<int>{5, 4, 3, 2, 1}, // reverse
                      std::vector<int>{3, 1, 4, 1, 5, 9, 2, 6,
                                       5},                  // random with dups
                      std::vector<int>{-5, -1, 0, 3, -2, 8} // with negatives
                      ));

} // anonymous namespace

// Custom main is not needed with gtest_main
// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
