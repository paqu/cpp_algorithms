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
std::vector<T> quickSort(const std::vector<T> &arr, Compare comp = Compare{});

template <typename T, typename Compare = std::less<T>>
void quickSortInPlace(std::vector<T> &arr, Compare comp = Compare{});
} // namespace algorithms::sorting
