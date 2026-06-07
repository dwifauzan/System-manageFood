#include "core/InventoryManager.h"
#include "core/Algorithms.h"
#include <algorithm>
#include <fstream>
#include <locale>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void InventoryManager::addItem(const BahanMakanan& item) {
    inventory.push_back(item);
}

void InventoryManager::removeItem(std::string_view name) {
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(),
        [name](const BahanMakanan& item) { return item.namaBahan == name; }),
        inventory.end());
}

void InventoryManager::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    for (const auto& item : inventory) {
        file << item.namaBahan << ","
             << item.stokSekarang << ","
             << item.kandunganNutrisi << ","
             << item.hargaBahan << ","
             << item.tanggalExpired << "\n";
    }
    file.close();
}

void InventoryManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    string messageFallback;

    if (!file.is_open()) {
        loadFromDummy();
        saveToCSV(filename);
        return;
    }

    inventory.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        BahanMakanan item;
        std::string val;

        std::getline(ss, item.namaBahan, ',');

        std::getline(ss, val, ',');
        item.stokSekarang = std::stoi(val);

        std::getline(ss, val, ',');
        item.kandunganNutrisi = std::stoi(val);

        std::getline(ss, val, ',');
        item.hargaBahan = std::stoi(val);

        std::getline(ss, item.tanggalExpired, ',');

        inventory.push_back(item);
    }
    file.close();
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

    // Binary search requires sorted data by name
    std::sort(inventory.begin(), inventory.end());

    auto indexOpt = algo::binarySearchByName(inventory, name);
    if (indexOpt.has_value()) {
        return &inventory[indexOpt.value()];
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
