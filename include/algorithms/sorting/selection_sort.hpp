#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Selection Sort Algorithm
 * Time: O(n²), Space: O(1)
 * Not stable
 */
template <typename T, typename Compare = std::less<T>>
std::vector<T> selectionSort(const std::vector<T> &arr,
                             Compare comp = Compare{});

template <typename T, typename Compare = std::less<T>>
void selectionSortInPlace(std::vector<T> &arr, Compare comp = Compare{});

} // namespace algorithms::sorting
