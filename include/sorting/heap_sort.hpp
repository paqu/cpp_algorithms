#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Heap Sort Algorithm
 * Time: O(n log n), Space: O(1)
 * Not stable
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> heapSort(const std::vector<T> &arr, Compare comp = Compare{});

template <typename T, typename Compare = std::less<T>>
void heapSortInPlace(std::vector<T> &arr, Compare comp = Compare{});

} // namespace algorithms::sorting
