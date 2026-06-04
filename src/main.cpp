#include <QApplication>
#include "gui/LoginDialog.h"
#include "gui/MainWindow.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w(login.getUsername(), login.getRole());
        w.show();
        return a.exec();
    }

    return 0;
}
