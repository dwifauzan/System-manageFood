#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include <QTableWidget>
#include "core/InventoryManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString &username, const QString &role, QWidget *parent = nullptr);

private:
    void setupInventoryTab();
    void setupMarketTab();
    void setupAdminTab();
    void refreshInventoryTable();

    QTabWidget *tabs;
    QTableWidget *inventoryTable;
    QString currentRole;
    InventoryManager invManager;
};

#endif // MAINWINDOW_H
