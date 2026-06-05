#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QTableWidget>
#include "core/InventoryManager.h"
#include "core/UserManager.h"

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

    QTabWidget *tabs;
    QTableWidget *inventoryTable;
    QTableWidget *userTable;
    QString currentRole;
    InventoryManager invManager;
    UserManager userManager;
};

#endif // MAINWINDOW_H
