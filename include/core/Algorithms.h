#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "BahanMakanan.h"
#include <vector>
#include <string>
#include <optional>
#include <string_view>

namespace algo {

// 1. Quick Sort
// Sort by expiry date (ascending: closest date first)
void quickSortByExpiry(std::vector<BahanMakanan>& items, int low, int high);

// 2. Binary Search
// Search by name. Returns index or std::nullopt.
// Prerequisite: vector must be sorted by name.
std::optional<size_t> binarySearchByName(const std::vector<BahanMakanan>& items, std::string_view targetName);

// 3. 0/1 Knapsack (Dynamic Programming)
// Returns the indices of items that maximize nutrition within the budget.
std::vector<size_t> solveKnapsack(const std::vector<BahanMakanan>& marketItems, int budget);

} // namespace algo

#endif // ALGORITHMS_H
