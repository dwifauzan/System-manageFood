#include "core/Algorithms.h"
#include <algorithm>
#include <iostream>

namespace algo {

// --- Quick Sort Helpers ---
int partition(std::vector<BahanMakanan>& items, int low, int high) {
    std::string pivot = items[high].tanggalExpired;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        // Sort by expiry date (YYYY-MM-DD string comparison works fine)
        if (items[j].tanggalExpired < pivot) {
            i++;
            std::swap(items[i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return (i + 1);
}

void quickSortByExpiry(std::vector<BahanMakanan>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);
        quickSortByExpiry(items, low, pi - 1);
        quickSortByExpiry(items, pi + 1, high);
    }
}

// --- Binary Search ---
int binarySearchByName(const std::vector<BahanMakanan>& items, const std::string& targetName) {
    int low = 0;
    int high = items.size() - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (items[mid].namaBahan == targetName)
            return mid;
        if (items[mid].namaBahan < targetName)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// --- 0/1 Knapsack ---
std::vector<int> solveKnapsack(const std::vector<BahanMakanan>& marketItems, int budget) {
    int n = marketItems.size();
    if (n == 0 || budget <= 0) return {};

    // dp[i][w] = max nutrition with i items and w budget
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(budget + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= budget; w++) {
            if (marketItems[i - 1].hargaBahan <= w) {
                dp[i][w] = std::max(marketItems[i - 1].kandunganNutrisi + dp[i - 1][w - marketItems[i - 1].hargaBahan],
                                    dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Reconstruct the selection
    std::vector<int> selectedIndices;
    int res = dp[n][budget];
    int w = budget;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            selectedIndices.push_back(i - 1);
            res -= marketItems[i - 1].kandunganNutrisi;
            w -= marketItems[i - 1].hargaBahan;
        }
    }

    return selectedIndices;
}

} // namespace algo
