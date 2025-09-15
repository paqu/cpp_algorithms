#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Insertion Sort Algorithm
 * Best: O(n), Average/Worst: O(n²), Space: O(1)
 * Stable sort
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> insertionSort(const std::vector<T> &arr,
                             Compare comp = Compare{});

template <typename T, typename Compare = std::less<T>>
void insertionSortInPlace(std::vector<T> &arr, Compare comp = Compare{});

} // namespace algorithms::sorting
