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
    int stokSekarang;
    int kandunganNutrisi;  // 'Value' for Knapsack
    int hargaBahan;        // 'Weight' for Knapsack
    std::string tanggalExpired; // Format: YYYY-MM-DD
};

#endif // BAHAN_MAKANAN_H
