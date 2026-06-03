#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QString>
#include "core/InventoryManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString &username, const QString &role, QWidget *parent = nullptr);

private:
    void setupInventoryTab();
    void setupMarketTab();
    void setupAdminTab();

    QTabWidget *tabs;
    QString currentRole;
    InventoryManager invManager;
};

#endif // MAINWINDOW_H
