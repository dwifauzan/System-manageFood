# DOKUMENTASI SISTEM & TRACK RECORD PROYEK
**Proyek:** Sistem Informasi Manajemen Inventaris Dapur & Optimasi Anggaran MBG (Makan Bergizi Gratis)

---

## 1. PRODUCT REQUIREMENT DOCUMENT (PRD) - REKAP
### Latar Belakang
Dapur MBG memerlukan efisiensi dalam pengelolaan stok bahan pangan untuk mencegah kadaluwarsa (waste) dan optimasi belanja harian agar nilai gizi maksimal dengan budget terbatas.

### Fitur Utama
- **Autentikasi Multi-role:** Admin (Monitoring & User) & Dapur (Operasional).
- **Manajemen Inventaris:** Visualisasi stok real-time.
- **Smart Market:** Rekomendasi belanja otomatis berbasis budget.
- **Fitur Pencarian:** Deteksi cepat bahan makanan di gudang.

---

## 2. TECH STACK & FRAMEWORK
- **Bahasa Pemrograman:** C++ (Standard 17).
- **GUI Framework:** **Qt 6 (Widgets)** - Digunakan untuk membangun antarmuka desktop yang stabil dan profesional.
- **Build System:** **CMake** - Digunakan untuk manajemen kompilasi dan dependensi lintas platform.
- **Algoritma Utama:**
  - **0/1 Knapsack (Dynamic Programming):** Logika optimasi belanja.
  - **Quick Sort:** Pengurutan stok FEFO (First Expired, First Out).
  - **Binary Search:** Pencarian data instan.

---

## 3. TRACK RECORD IMPLEMENTASI (LOG)
### [Juni 3, 2026] - Tahap Inisialisasi & Core Logic
- **Arsitektur:** Pembuatan struktur folder `include/` dan `src/`.
- **Core Logic:** Implementasi `BahanMakanan.h` dan `Algorithms.cpp`.
- **Validasi:** Pembuatan unit test `test_algorithms.cpp` untuk memastikan akurasi Knapsack, Quick Sort, dan Binary Search. Hasil: **100% Passed**.

### [Juni 3, 2026] - Tahap GUI & Integration
- **Login System:** Implementasi `LoginDialog` dengan validasi role-based.
- **Dashboard:** Implementasi `MainWindow` dengan sistem Tab.
- **Fitur Inventaris:** Integrasi Quick Sort pada tabel stok dan Binary Search pada kolom pencarian.
- **Fitur Smart Market:** Integrasi algoritma Knapsack pada katalog pasar dummy untuk rekomendasi belanja.
- **Admin Panel:** Implementasi view khusus untuk monitoring finansial dan user list.

---

## 4. ROADMAP PENGEMBANGAN (FUTURE)
### Tahap 1: Database Persistence (Q3 2026)
- Migrasi dari data dummy (hardcoded) ke SQLite atau PostgreSQL untuk penyimpanan data permanen.
- Implementasi enkripsi password pada database.

### Tahap 2: Laporan & Export (Q4 2026)
- Fitur ekspor laporan stok dan belanja ke format PDF atau Excel.
- Grafik statistik pengeluaran mingguan menggunakan Qt Charts.

### Tahap 3: Mobile Sync (2027)
- Pengembangan API menggunakan C++ Rest SDK untuk sinkronisasi data dengan aplikasi mobile petugas lapangan.
- Integrasi Barcode/QR Code Scanner untuk input stok masuk lebih cepat.

---

## 5. STRUKTUR FILE AKHIR
```text
proyekalgo/
├── CMakeLists.txt        # Konfigurasi Build
├── README.md             # Instruksi Cepat
├── SYSTEM_DOCS.md        # Dokumentasi ini
├── include/              # Header Files
│   ├── core/             # Logika Algoritma
│   └── gui/              # Komponen Antarmuka
├── src/                  # Source Files
│   ├── core/
│   ├── gui/
│   └── main.cpp          # Entry Point
└── tests/                # Unit Testing
```
