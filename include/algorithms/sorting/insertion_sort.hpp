#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * In-place insertion sort implementation
 * Sorts the given vector in-place using insertion sort algorithm
 */
template <typename T, typename Compare = std::less<T>>
void insertion_sort_impl(std::vector<T> &arr, Compare comp = Compare{}) {
    if (arr.size() <= 1)
        return;

    for (size_t i = 1; i < arr.size(); ++i) {
        T key = std::move(arr[i]);
        size_t j = i;

        // Move elements that are greater than key one position ahead
        while (j > 0 && comp(key, arr[j - 1])) {
            arr[j] = std::move(arr[j - 1]);
            --j;
        }

        // Place key at its correct position
        arr[j] = std::move(key);
    }
}

/**
 * Insertion Sort Algorithm
 * Best: O(n), Average/Worst: O(n²), Space: O(1)
 * Stable sort
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> insertion_sort(const std::vector<T> &arr,
                              Compare comp = Compare{}) {
    std::vector<T> result = arr; // Copy the input
    insertion_sort_impl(result, comp);
    return result;
}

} // namespace algorithms::sorting
