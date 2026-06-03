#ifndef BAHAN_MAKANAN_H
#define BAHAN_MAKANAN_H

#include <string>
#include <vector>

/**
 * @struct BahanMakanan
 * @brief Represents a food ingredient entity in the system.
 */
struct BahanMakanan {
    std::string namaBahan;
    int stokSekarang = 0;
    int kandunganNutrisi = 0;  // 'Value' for Knapsack
    int hargaBahan = 0;        // 'Weight' for Knapsack
    std::string tanggalExpired; // Format: YYYY-MM-DD

    // For Binary Search and sorting by name
    bool operator<(const BahanMakanan& other) const {
        return namaBahan < other.namaBahan;
    }
};

#endif // BAHAN_MAKANAN_H
