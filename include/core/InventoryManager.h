#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "BahanMakanan.h"
#include <vector>
#include <string>

#include <optional>
#include <string_view>

class InventoryManager {
public:
    void addItem(const BahanMakanan& item);
    void removeItem(std::string_view name);
    std::vector<BahanMakanan> getSortedItemsByExpiry();
    std::optional<BahanMakanan*> findItemByName(std::string_view name);
    
    const std::vector<BahanMakanan>& getInventory() const { return inventory; }

    // CSV Persistence
    void saveToCSV(const std::string& filename);
    void loadFromCSV(const std::string& filename);

    // Dummy persistence (could be file-based)
    void loadFromDummy();

private:
    std::vector<BahanMakanan> inventory;
};

#endif // INVENTORY_MANAGER_H
