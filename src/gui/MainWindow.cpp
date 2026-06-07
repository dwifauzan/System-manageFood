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
#include <QComboBox>

using namespace std;

MainWindow::MainWindow(const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent), currentRole(role), financialLabel(nullptr) {
    
    setWindowTitle("Sistem Inventaris MBG - " + username + " (" + role + ")");
    resize(800, 600);

    invManager.loadFromCSV("inventory.csv");
    userManager.loadFromCSV("users.csv");
    finManager.loadFromCSV("financials.csv");

    tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    setupInventoryTab();
    setupMarketTab();
    
    if (role == "Admin") {
        setupAdminTab();
    }
}

void MainWindow::refreshFinancials() {
    if (!financialLabel) return;
    financialLabel->setText(QString("Total Anggaran Terpakai: Rp %1\nSisa Anggaran: Rp %2")
        .arg(finManager.getSpent())
        .arg(finManager.getRemaining()));
}

void MainWindow::refreshInventoryTable() {
    if (!inventoryTable) return;

    const auto& items = invManager.getInventory();
    inventoryTable->setRowCount(0);
    for (const auto& item : items) {
        int row = inventoryTable->rowCount();
        inventoryTable->insertRow(row);
        inventoryTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(item.namaBahan)));
        inventoryTable->setItem(row, 1, new QTableWidgetItem(QString::number(item.stokSekarang)));
        inventoryTable->setItem(row, 2, new QTableWidgetItem(QString::number(item.kandunganNutrisi)));
        inventoryTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(item.tanggalExpired)));
    }
}

void MainWindow::refreshUserTable() {
    if (!userTable) return;

    const auto& users = userManager.getUsers();
    userTable->setRowCount(0);
    for (const auto& user : users) {
        int row = userTable->rowCount();
        userTable->insertRow(row);
        userTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(user.username)));
        userTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(user.role)));
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
    inventoryTable = new QTableWidget(0, 4);
    inventoryTable->setHorizontalHeaderLabels({"Nama", "Stok", "Nutrisi", "Expired"});
    inventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    inventoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    inventoryTable->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(inventoryTable);

    // Add/Remove Buttons
    QHBoxLayout *actionLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Add Item");
    QPushButton *removeBtn = new QPushButton("Remove Selected");
    actionLayout->addWidget(addBtn);
    actionLayout->addWidget(removeBtn);
    layout->addLayout(actionLayout);

    refreshInventoryTable();

    connect(addBtn, &QPushButton::clicked, [this]() {
        bool ok;
        QString name = QInputDialog::getText(this, "Add Item", "Nama Bahan:", QLineEdit::Normal, "", &ok);
        if (!ok || name.isEmpty()) return;

        int stok = QInputDialog::getInt(this, "Add Item", "Stok Sekarang:", 0, 0, 10000, 1, &ok);
        if (!ok) return;

        int nutri = QInputDialog::getInt(this, "Add Item", "Kandungan Nutrisi:", 0, 0, 10000, 1, &ok);
        if (!ok) return;

        QString exp = QInputDialog::getText(this, "Add Item", "Tanggal Expired (YYYY-MM-DD):", QLineEdit::Normal, "2026-06-01", &ok);
        if (!ok) return;

        BahanMakanan newItem{name.toStdString(), stok, nutri, 0, exp.toStdString()};
        invManager.addItem(newItem);
        invManager.saveToCSV("inventory.csv");
        refreshInventoryTable();
    });

    connect(removeBtn, &QPushButton::clicked, [this]() {
        int row = inventoryTable->currentRow();
        if (row < 0) {
            QMessageBox::warning(this, "Warning", "Please select an item to remove.");
            return;
        }

        QString name = inventoryTable->item(row, 0)->text();
        auto reply = QMessageBox::question(this, "Confirm", "Remove " + name + "?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            invManager.removeItem(name.toStdString());
            invManager.saveToCSV("inventory.csv");
            refreshInventoryTable();
        }
    });

    connect(sortBtn, &QPushButton::clicked, [this]() {
        auto sorted = invManager.getSortedItemsByExpiry();
        inventoryTable->setRowCount(0);
        for (const auto& item : sorted) {
            int r = inventoryTable->rowCount();
            inventoryTable->insertRow(r);
            inventoryTable->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(item.namaBahan)));
            inventoryTable->setItem(r, r == 0 ? 1 : 1, new QTableWidgetItem(QString::number(item.stokSekarang)));
            inventoryTable->setItem(r, 2, new QTableWidgetItem(QString::number(item.kandunganNutrisi)));
            inventoryTable->setItem(r, 3, new QTableWidgetItem(QString::fromStdString(item.tanggalExpired)));
        }
    });

    connect(searchBtn, &QPushButton::clicked, [this, searchEdit]() {
        string target = searchEdit->text().toStdString();
        auto result = invManager.findItemByName(target);
        
        if (result.has_value()) {
            BahanMakanan* item = result.value();
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
    
    vector<BahanMakanan> marketItems = {
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

        vector<size_t> selected = algo::solveKnapsack(marketItems, budget);
        
        if (selected.empty()) {
            QMessageBox::information(this, "Hasil", "Tidak ada barang yang terbeli dengan budget tersebut.");
            return;
        }

        QString result = "Rekomendasi Belanja Terbeli:\n\n";
        int totalNutri = 0;
        int totalCost = 0;

        for (size_t idx : selected) {
            const auto& mItem = marketItems[idx];
            result += QString("- %1 (Nutrisi: %2, Harga: %3)\n")
                .arg(QString::fromStdString(mItem.namaBahan))
                .arg(mItem.kandunganNutrisi)
                .arg(mItem.hargaBahan);
            
            totalNutri += mItem.kandunganNutrisi;
            totalCost += mItem.hargaBahan;

            finManager.addExpense(mItem.hargaBahan);

            auto existing = invManager.findItemByName(mItem.namaBahan);
            if (existing.has_value()) {
                existing.value()->stokSekarang += 1;
            } else {
                BahanMakanan newItem{mItem.namaBahan, 1, mItem.kandunganNutrisi, mItem.hargaBahan, "2026-12-31"};
                invManager.addItem(newItem);
            }
        }
        
        invManager.saveToCSV("inventory.csv");
        finManager.saveToCSV("financials.csv");
        refreshInventoryTable();
        refreshFinancials();

        result += QString("\nTotal Nutrisi: %1\nTotal Biaya: Rp %2\n\nStok Inventaris telah diperbarui!")
            .arg(totalNutri).arg(totalCost);

        QMessageBox::information(this, "Optimasi & Update Berhasil", result);
    });

    tabs->addTab(tab, "Pasar & Optimasi");
}

void MainWindow::setupAdminTab() {
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    
    layout->addWidget(new QLabel("Panel Kontrol Admin"));
    
    userTable = new QTableWidget(0, 2);
    userTable->setHorizontalHeaderLabels({"Username", "Role"});
    userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layout->addWidget(new QLabel("Manajemen Pengguna:"));
    layout->addWidget(userTable);

    refreshUserTable();

    QPushButton *addUserBtn = new QPushButton("Add New User");
    layout->addWidget(addUserBtn);

    connect(addUserBtn, &QPushButton::clicked, [this]() {
        QDialog dialog(this);
        dialog.setWindowTitle("Add New User");
        QVBoxLayout layout(&dialog);

        QLineEdit *userEdit = new QLineEdit();
        userEdit->setPlaceholderText("Username");
        layout.addWidget(new QLabel("Username:"));
        layout.addWidget(userEdit);

        QLineEdit *passEdit = new QLineEdit();
        passEdit->setPlaceholderText("Password");
        passEdit->setEchoMode(QLineEdit::Password);
        layout.addWidget(new QLabel("Password:"));
        layout.addWidget(passEdit);

        QComboBox *roleCombo = new QComboBox();
        roleCombo->addItems({"Admin", "Dapur"});
        layout.addWidget(new QLabel("Role:"));
        layout.addWidget(roleCombo);

        QPushButton *saveBtn = new QPushButton("Save");
        layout.addWidget(saveBtn);

        connect(saveBtn, &QPushButton::clicked, [&]() {
            QString username = userEdit->text();
            QString password = passEdit->text();
            QString role = roleCombo->currentText();

            if (username.isEmpty() || password.isEmpty()) {
                QMessageBox::warning(&dialog, "Error", "Username and password cannot be empty.");
                return;
            }

            if (userManager.userExists(username.toStdString())) {
                QMessageBox::warning(&dialog, "Error", "User already exists.");
                return;
            }

            userManager.addUser({username.toStdString(), password.toStdString(), role.toStdString()});
            userManager.saveToCSV("users.csv");
            refreshUserTable();
            dialog.accept();
        });

        dialog.exec();
    });

    layout->addWidget(new QLabel("Rekapitulasi Anggaran:"));
    financialLabel = new QLabel();
    financialLabel->setStyleSheet("font-weight: bold; color: blue;");
    layout->addWidget(financialLabel);
    refreshFinancials();

    QPushButton *setBudgetBtn = new QPushButton("Set Total Budget");
    layout->addWidget(setBudgetBtn);

    connect(setBudgetBtn, &QPushButton::clicked, [this]() {
        bool ok;
        int newBudget = QInputDialog::getInt(this, "Set Budget", "Total Budget (Rp):", finManager.getBudget(), 0, 100000000, 10000, &ok);
        if (ok) {
            finManager.setBudget(newBudget);
            finManager.saveToCSV("financials.csv");
            refreshFinancials();
        }
    });

    tabs->addTab(tab, "Admin");
}
