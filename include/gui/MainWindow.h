#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QTableWidget>
#include <QLabel>
#include "core/InventoryManager.h"
#include "core/UserManager.h"
#include "core/FinancialManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString &username, const QString &role, QWidget *parent = nullptr);

private:
    void setupInventoryTab();
    void setupMarketTab();
    void setupAdminTab();
    void refreshInventoryTable();
    void refreshUserTable();
    void refreshFinancials();

    QTabWidget *tabs;
    QTableWidget *inventoryTable;
    QTableWidget *userTable;
    QLabel *financialLabel;
    QString currentRole;
    InventoryManager invManager;
    UserManager userManager;
    FinancialManager finManager;
};

#endif // MAINWINDOW_H
