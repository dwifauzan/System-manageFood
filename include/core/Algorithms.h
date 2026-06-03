#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "BahanMakanan.h"
#include <vector>
#include <string>

namespace algo {

// 1. Quick Sort
// Sort by expiry date (ascending: closest date first)
void quickSortByExpiry(std::vector<BahanMakanan>& items, int low, int high);

// 2. Binary Search
// Search by name (case-insensitive recommended). Returns index or -1.
// Prerequisite: vector must be sorted by name.
int binarySearchByName(const std::vector<BahanMakanan>& items, const std::string& targetName);

// 3. 0/1 Knapsack (Dynamic Programming)
// Returns the indices of items that maximize nutrition within the budget.
std::vector<int> solveKnapsack(const std::vector<BahanMakanan>& marketItems, int budget);

} // namespace algo

#endif // ALGORITHMS_H
