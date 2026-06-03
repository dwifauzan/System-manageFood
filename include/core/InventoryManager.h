#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "BahanMakanan.h"
#include <vector>
#include <string>

class InventoryManager {
public:
    void addItem(const BahanMakanan& item);
    void removeItem(const std::string& name);
    std::vector<BahanMakanan> getSortedItemsByExpiry();
    BahanMakanan* findItemByName(const std::string& name);
    
    const std::vector<BahanMakanan>& getInventory() const { return inventory; }

    // Dummy persistence (could be file-based)
    void loadFromDummy();

private:
    std::vector<BahanMakanan> inventory;
};

#endif // INVENTORY_MANAGER_H
