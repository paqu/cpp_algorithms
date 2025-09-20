#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * In-place selection sort implementation
 * Sorts the given vector in-place using selection sort algorithm
 */
template <typename T, typename Compare = std::less<T>>
void selection_sort_impl(std::vector<T> &arr, Compare comp = Compare{}) {
    if (arr.size() <= 1)
        return;

    for (size_t i = 0; i < arr.size() - 1; ++i) {
        // Find the minimum/maximum element in the remaining unsorted array
        size_t target_idx = i;

        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (comp(arr[j], arr[target_idx])) {
                target_idx = j;
            }
        }

        // Swap the found minimum/maximum element with the first element
        if (target_idx != i) {
            std::swap(arr[i], arr[target_idx]);
        }
    }
}

/**
 * Selection Sort Algorithm
 * Time: O(n²), Space: O(1)
 * Not stable
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> selection_sort(const std::vector<T> &arr,
                              Compare comp = Compare{}) {
    std::vector<T> result = arr; // Copy the input
    selection_sort_impl(result, comp);
    return result;
}

} // namespace algorithms::sorting
