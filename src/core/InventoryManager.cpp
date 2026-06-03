#include "core/InventoryManager.h"
#include "core/Algorithms.h"
#include <algorithm>

void InventoryManager::addItem(const BahanMakanan& item) {
    inventory.push_back(item);
}

void InventoryManager::removeItem(std::string_view name) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
        [name](const BahanMakanan& item) { return item.namaBahan == name; }),
        inventory.end());
}

std::vector<BahanMakanan> InventoryManager::getSortedItemsByExpiry() {
    std::vector<BahanMakanan> sorted = inventory;
    if (!sorted.empty()) {
        algo::quickSortByExpiry(sorted, 0, static_cast<int>(sorted.size()) - 1);
    }
    return sorted;
}

std::optional<BahanMakanan*> InventoryManager::findItemByName(std::string_view name) {
    if (inventory.empty()) return std::nullopt;

    // Sort for binary search (using the new operator<)
    std::vector<BahanMakanan> temp = inventory;
    std::sort(temp.begin(), temp.end());

    auto indexOpt = algo::binarySearchByName(temp, name);
    if (indexOpt.has_value()) {
        // Find original pointer
        for (auto& item : inventory) {
            if (item.namaBahan == name) return &item;
        }
    }
    return std::nullopt;
}

void InventoryManager::loadFromDummy() {
    inventory = {
        {"Beras", 100, 100, 15000, "2026-12-01"},
        {"Ayam", 20, 85, 45000, "2026-06-15"},
        {"Telur", 50, 70, 25000, "2026-06-10"},
        {"Sawi", 15, 40, 5000, "2026-06-05"},
        {"Minyak", 30, 50, 18000, "2026-11-20"}
    };
}
