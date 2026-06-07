#include "core/FinancialManager.h"
#include <fstream>
#include <sstream>

void FinancialManager::saveToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;
    file << totalBudget << "," << totalSpent << "\n";
    file.close();
}

void FinancialManager::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Defaults already set in constructor
        saveToCSV(filename);
        return;
    }

    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string val;
        if (std::getline(ss, val, ',')) totalBudget = std::stoi(val);
        if (std::getline(ss, val, ',')) totalSpent = std::stoi(val);
    }
    file.close();
}
