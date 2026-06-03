#include "gui/MainWindow.h"
#include "core/Algorithms.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent), currentRole(role) {
    
    setWindowTitle("Sistem Inventaris MBG - " + username + " (" + role + ")");
    resize(800, 600);

    invManager.loadFromDummy();

    tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    setupInventoryTab();
    setupMarketTab();
    
    if (role == "Admin") {
        setupAdminTab();
    }
}

void MainWindow::setupInventoryTab() {
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    // Search and Sort Bar
    QHBoxLayout *topBar = new QHBoxLayout();
    QLineEdit *searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Search item by name...");
    QPushButton *searchBtn = new QPushButton("Search (Binary Search)");
    QPushButton *sortBtn = new QPushButton("Sort by Expiry (Quick Sort)");
    
    topBar->addWidget(searchEdit);
    topBar->addWidget(searchBtn);
    topBar->addWidget(sortBtn);
    layout->addLayout(topBar);

    // Table
    QTableWidget *table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({"Nama", "Stok", "Nutrisi", "Expired"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(table);

    auto refreshTable = [table, this](const std::vector<BahanMakanan>& items) {
        table->setRowCount(0);
        for (const auto& item : items) {
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(item.namaBahan)));
            table->setItem(row, 1, new QTableWidgetItem(QString::number(item.stokSekarang)));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(item.kandunganNutrisi)));
            table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(item.tanggalExpired)));
        }
    };

    refreshTable(invManager.getInventory());

    connect(sortBtn, &QPushButton::clicked, [this, refreshTable]() {
        refreshTable(invManager.getSortedItemsByExpiry());
    });

    connect(searchBtn, &QPushButton::clicked, [this, searchEdit, table]() {
        std::string target = searchEdit->text().toStdString();
        BahanMakanan* item = invManager.findItemByName(target);
        if (item) {
            QMessageBox::information(this, "Search Result", 
                QString("Found: %1\nStok: %2\nExpired: %3")
                .arg(QString::fromStdString(item->namaBahan))
                .arg(item->stokSekarang)
                .arg(QString::fromStdString(item->tanggalExpired)));
        } else {
            QMessageBox::warning(this, "Search Result", "Item not found.");
        }
    });

    tabs->addTab(tab, "Inventaris");
}

void MainWindow::setupMarketTab() {
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);

    layout->addWidget(new QLabel("Pasar Dummy - Rekomendasi Belanja Pintar"));

    QTableWidget *marketTable = new QTableWidget(0, 3);
    marketTable->setHorizontalHeaderLabels({"Nama Bahan", "Nutrisi (Value)", "Harga (Weight)"});
    marketTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    std::vector<BahanMakanan> marketItems = {
        {"Daging Sapi", 0, 90, 120000, ""},
        {"Daging Ayam", 0, 80, 40000, ""},
        {"Ikan Kembung", 0, 75, 30000, ""},
        {"Telur Puyuh", 0, 60, 25000, ""},
        {"Tempe", 0, 50, 5000, ""},
        {"Tahu", 0, 45, 4000, ""},
        {"Bayam", 0, 40, 3000, ""},
        {"Wortel", 0, 35, 7000, ""}
    };

    for (const auto& item : marketItems) {
        int row = marketTable->rowCount();
        marketTable->insertRow(row);
        marketTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(item.namaBahan)));
        marketTable->setItem(row, 1, new QTableWidgetItem(QString::number(item.kandunganNutrisi)));
        marketTable->setItem(row, 2, new QTableWidgetItem(QString::number(item.hargaBahan)));
    }
    layout->addWidget(marketTable);

    QHBoxLayout *budgetBar = new QHBoxLayout();
    budgetBar->addWidget(new QLabel("Budget Belanja (Rp):"));
    QLineEdit *budgetEdit = new QLineEdit("50000");
    QPushButton *calcBtn = new QPushButton("Optimasi Belanja (0/1 Knapsack)");
    budgetBar->addWidget(budgetEdit);
    budgetBar->addWidget(calcBtn);
    layout->addLayout(budgetBar);

    connect(calcBtn, &QPushButton::clicked, [this, budgetEdit, marketItems]() {
        bool ok;
        int budget = budgetEdit->text().toInt(&ok);
        if (!ok || budget <= 0) {
            QMessageBox::warning(this, "Error", "Masukkan budget yang valid.");
            return;
        }

        std::vector<int> selected = algo::solveKnapsack(marketItems, budget);
        
        QString result = "Rekomendasi Belanja (Nutrisi Maksimal):\n\n";
        int totalNutri = 0;
        int totalCost = 0;
        for (int idx : selected) {
            result += QString("- %1 (Nutrisi: %2, Harga: %3)\n")
                .arg(QString::fromStdString(marketItems[idx].namaBahan))
                .arg(marketItems[idx].kandunganNutrisi)
                .arg(marketItems[idx].hargaBahan);
            totalNutri += marketItems[idx].kandunganNutrisi;
            totalCost += marketItems[idx].hargaBahan;
        }
        result += QString("\nTotal Nutrisi: %1\nTotal Biaya: Rp %2")
            .arg(totalNutri).arg(totalCost);

        QMessageBox::information(this, "Hasil Optimasi Knapsack", result);
    });

    tabs->addTab(tab, "Pasar & Optimasi");
}

void MainWindow::setupAdminTab() {
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    
    layout->addWidget(new QLabel("Panel Kontrol Admin"));
    
    QTableWidget *userTable = new QTableWidget(2, 2);
    userTable->setHorizontalHeaderLabels({"Username", "Role"});
    userTable->setItem(0, 0, new QTableWidgetItem("admin"));
    userTable->setItem(0, 1, new QTableWidgetItem("Admin"));
    userTable->setItem(1, 0, new QTableWidgetItem("dapur"));
    userTable->setItem(1, 1, new QTableWidgetItem("Dapur"));
    layout->addWidget(new QLabel("Manajemen Pengguna:"));
    layout->addWidget(userTable);

    layout->addWidget(new QLabel("Rekapitulasi Anggaran:"));
    QLabel *financialLabel = new QLabel("Total Anggaran Terpakai: Rp 1.250.000\nSisa Anggaran: Rp 3.750.000");
    financialLabel->setStyleSheet("font-weight: bold; color: blue;");
    layout->addWidget(financialLabel);

    tabs->addTab(tab, "Admin");
}
