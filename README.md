# Sistem Informasi Manajemen Inventaris Dapur MBG

Aplikasi Desktop (C++ GUI) untuk manajemen inventaris dapur dan optimasi anggaran belanja menggunakan algoritma 0/1 Knapsack, Quick Sort, dan Binary Search.

## Fitur Utama
1. **Autentikasi:** Login untuk Admin dan Petugas Dapur.
2. **Manajemen Stok:** Menampilkan stok barang dengan pengurutan **Quick Sort** (FEFO - First Expired, First Out).
3. **Pencarian Cepat:** Mencari bahan makanan menggunakan **Binary Search**.
4. **Optimasi Belanja:** Fitur "Smart Market" menggunakan **0/1 Knapsack** untuk memaksimalkan gizi dalam batasan budget.
5. **Admin Panel:** Monitoring finansial dan manajemen pengguna.

## Algoritma yang Digunakan
- **0/1 Knapsack (Dynamic Programming):** Digunakan untuk memilih kombinasi bahan makanan terbaik di pasar agar mendapatkan nilai gizi maksimal tanpa melebihi budget.
- **Quick Sort:** Digunakan untuk mengurutkan stok berdasarkan tanggal kedaluwarsa secara efisien (O(n log n)).
- **Binary Search:** Digunakan untuk pencarian data instan (O(log n)).

## Teknologi
- **Bahasa:** C++ (Standard 17)
- **GUI Framework:** Qt 6
- **Build System:** CMake

## Cara Build & Run
1. Pastikan **Qt 6** dan **CMake** sudah terinstall.
2. Clone repository ini.
3. Jalankan perintah berikut:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./InventarisMBG
   ```

## Akun Demo
- **Admin:** `admin` / `admin123`
- **Dapur:** `dapur` / `dapur123`
