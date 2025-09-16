#pragma once

#include "sorting/heap_sort.hpp"
#include "sorting/insertion_sort.hpp"
#include "sorting/merge_sort.hpp"
#include "sorting/quick_sort.hpp"
#include "sorting/selection_sort.hpp"

namespace algorithms {
namespace sorting {
// Re-export algorithms from the implementation namespace
using algorithms::sorting::heapSort;
using algorithms::sorting::insertionSort;
using algorithms::sorting::mergeSort;
using algorithms::sorting::quickSort;
using algorithms::sorting::selectionSort;
} // namespace sorting
} // namespace algorithms
