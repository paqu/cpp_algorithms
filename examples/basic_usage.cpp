#include <algorithms/sorting/quick_sort.hpp>
#include <iostream>

int main() {
    std::vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "=== Basic Sorting Examples ===" << std::endl;

    auto sorted_asc = algorithms::sorting::quick_sort(numbers);
    std::cout << "Sorted ascending: ";
    for (int x : sorted_asc) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    auto sorted_desc =
        algorithms::sorting::quick_sort(numbers, std::greater<int>{});
    std::cout << "Sorted descending: ";
    for (int x : sorted_desc) {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // Example 2: String sorting
    std::vector<std::string> words = {"banana", "apple", "cherry", "date",
                                      "elderberry"};

    std::cout << "Original words: ";
    for (const auto &word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    auto sorted_words = algorithms::sorting::quick_sort(words);
    std::cout << "Sorted alphabetically: ";
    for (const auto &word : sorted_words) {
        std::cout << word << " ";
    }
    std::cout << "\n\n";

    // Example 3: Sort by string length
    auto sorted_by_length = algorithms::sorting::quick_sort(
        words, [](const std::string &a, const std::string &b) {
            return a.length() < b.length();
        });

    std::cout << "Sorted by length: ";
    for (const auto &word : sorted_by_length) {
        std::cout << word << " ";
    }
    std::cout << "\n\n";

    // Example 4: Edge cases
    std::vector<int> empty_vec;
    std::vector<int> single_element = {42};
    std::vector<int> duplicates = {5, 3, 5, 3, 1, 5, 1};

    auto sorted_empty = algorithms::sorting::quick_sort(empty_vec);
    auto sorted_single = algorithms::sorting::quick_sort(single_element);
    auto sorted_duplicates = algorithms::sorting::quick_sort(duplicates);

    std::cout << "Edge cases:\n";
    std::cout << "Empty vector: ";
    for (int x : sorted_empty)
        std::cout << x << " ";
    std::cout << "(size: " << sorted_empty.size() << ")\n";

    std::cout << "Single element: ";
    for (int x : sorted_single)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "With duplicates: ";
    for (int x : sorted_duplicates)
        std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n✅ All examples completed successfully!\n";
    return 0;
}
