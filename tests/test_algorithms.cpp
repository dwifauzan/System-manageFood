#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include "core/Algorithms.h"
#include "core/BahanMakanan.h"

void testQuickSort() {
    std::cout << "Testing Quick Sort (Expiry)..." << std::endl;
    std::vector<BahanMakanan> items = {
        {"Ayam", 10, 80, 50000, "2026-06-10"},
        {"Beras", 50, 100, 15000, "2026-12-31"},
        {"Susu", 5, 60, 20000, "2026-06-05"}
    };
    algo::quickSortByExpiry(items, 0, static_cast<int>(items.size()) - 1);
    
    assert(items[0].namaBahan == "Susu");
    assert(items[1].namaBahan == "Ayam");
    assert(items[2].namaBahan == "Beras");
    std::cout << "Quick Sort Passed!" << std::endl;
}

void testBinarySearch() {
    std::cout << "Testing Binary Search..." << std::endl;
    std::vector<BahanMakanan> items = {
        {"Ayam", 10, 80, 50000, "2026-06-10"},
        {"Beras", 50, 100, 15000, "2026-12-31"},
        {"Susu", 5, 60, 20000, "2026-06-05"}
    };
    // Sort by name first for binary search (using the new operator<)
    std::sort(items.begin(), items.end());

    auto result = algo::binarySearchByName(items, "Beras");
    assert(result.has_value());
    assert(items[result.value()].namaBahan == "Beras");

    auto resultFail = algo::binarySearchByName(items, "Daging");
    assert(!resultFail.has_value());
    std::cout << "Binary Search Passed!" << std::endl;
}

void testKnapsack() {
    std::cout << "Testing Knapsack (Budget Optimization)..." << std::endl;
    std::vector<BahanMakanan> market = {
        {"Telur", 0, 10, 2000, ""},
        {"Tempe", 0, 15, 3000, ""},
        {"Daging", 0, 40, 15000, ""},
        {"Sayur", 0, 5, 1000, ""}
    };
    int budget = 5000;
    
    std::vector<size_t> selected = algo::solveKnapsack(market, budget);
    
    int totalCost = 0;
    int totalNutri = 0;
    for (size_t idx : selected) {
        totalCost += market[idx].hargaBahan;
        totalNutri += market[idx].kandunganNutrisi;
    }

    assert(totalCost <= budget);
    // Best combo for 5000: Tempe (15) + Telur (10) = 25 nutri, cost 5000. 
    assert(totalNutri == 25); 
    std::cout << "Knapsack Passed!" << std::endl;
}

int main() {
    testQuickSort();
    testBinarySearch();
    testKnapsack();
    std::cout << "All Core Tests Passed!" << std::endl;
    return 0;
}
