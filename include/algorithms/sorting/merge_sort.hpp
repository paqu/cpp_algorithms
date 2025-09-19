#pragma once
#include <functional>
#include <vector>

namespace algorithms::sorting {

/**
 * Helper function to merge two sorted subarrays
 * Merges arr[left...mid] and arr[mid+1...right] in sorted order
 */
template <typename T, typename Compare>
void merge(std::vector<T> &arr, int left, int mid, int right, Compare comp) {

    int left_size = mid - left + 1;
    int right_size = right - mid;

    std::vector<T> left_arr(left_size);
    std::vector<T> right_arr(right_size);

    for (int i = 0; i < left_size; i++) {
        left_arr[i] = std::move(arr[left + i]);
    }
    for (int i = 0; i < right_size; i++) {
        right_arr[i] = std::move(arr[mid + 1 + i]);
    }

    int i = 0;    // Initial index of left subarray
    int j = 0;    // Initial index of right subarray
    int k = left; // Initial index of merged subarray

    while (i < left_size && j < right_size) {
        if (comp(left_arr[i], right_arr[j]) ||
            !comp(right_arr[j], left_arr[i])) {
            // left_arr[i] <= right_arr[j] (stable comparison)
            arr[k] = std::move(left_arr[i]);
            i++;
        } else {
            arr[k] = std::move(right_arr[j]);
            j++;
        }
        k++;
    }

    // Copy remaining elements of left_arr[], if any
    while (i < left_size) {
        arr[k] = std::move(left_arr[i]);
        i++;
        k++;
    }

    // Copy remaining elements of right_arr[], if any
    while (j < right_size) {
        arr[k] = std::move(right_arr[j]);
        j++;
        k++;
    }
}

/**
 * Recursive merge sort implementation
 */
template <typename T, typename Compare>
void merge_sort_impl(std::vector<T> &arr, int left, int right, Compare comp) {
    if (left >= right) {
        return; // Base case: single element or empty
    }

    // Find the middle point to divide the array into two halves
    int mid = left + (right - left) / 2;

    // Recursively sort both halves
    merge_sort_impl(arr, left, mid, comp);
    merge_sort_impl(arr, mid + 1, right, comp);

    // Merge the sorted halves
    merge(arr, left, mid, right, comp);
}

/**
 * Merge Sort Algorithm
 * Time: O(n log n), Space: O(n)
 * Stable sort
 */

template <typename T, typename Compare = std::less<T>>
std::vector<T> merge_sort(const std::vector<T> &arr, Compare comp = Compare{}) {
    std::vector<T> result = arr; // Copy the input
    if (!result.empty()) {
        merge_sort_impl(result, 0, static_cast<int>(result.size()) - 1, comp);
    }
    return result;
}

} // namespace algorithms::sorting
