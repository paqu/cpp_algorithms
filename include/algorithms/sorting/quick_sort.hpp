#pragma once

#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Quick Sort Algorithm
 * Average: O(n log n), Worst: O(n²), Space: O(log n)
 * Not stable
 */
template <typename T, typename Compare = std::less<T>>
void quick_sort_impl(std::vector<T> &arr, int left, int right, Compare comp) {
    if (left >= right)
        return;

    // Choose pivot (middle element)
    T pivot = arr[left + (right - left) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (comp(arr[i], pivot))
            i++; // arr[i] < pivot
        while (comp(pivot, arr[j]))
            j--; // arr[j] > pivot

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    // Recurse on partitions
    if (left < j)
        quick_sort_impl(arr, left, j, comp);
    if (i < right)
        quick_sort_impl(arr, i, right, comp);
}

template <typename T, typename Compare = std::less<T>>
void quick_sort(std::vector<T> &arr, Compare comp = Compare{}) {
    if (!arr.empty()) {
        quick_sort_impl(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

} // namespace algorithms::sorting
