#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Merge Sort Algorithm
 * Time: O(n log n), Space: O(n)
 * Stable sort
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> mergeSort(const std::vector<T> &arr, Compare comp = Compare{});

} // namespace algorithms::sorting
