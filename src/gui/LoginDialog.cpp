#include "gui/LoginDialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Login - Inventaris MBG");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("Username:"));
    usernameEdit = new QLineEdit();
    layout->addWidget(usernameEdit);
    
    layout->addWidget(new QLabel("Password:"));
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);
    
    QPushButton *loginBtn = new QPushButton("Login");
    layout->addWidget(loginBtn);
    
    connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::handleLogin);
}

void LoginDialog::handleLogin() {
    QString user = usernameEdit->text();
    QString pass = passwordEdit->text();
    
    // Simple hardcoded auth for demo
    if (user == "admin" && pass == "admin123") {
        username = user;
        role = "Admin";
        accept();
    } else if (user == "dapur" && pass == "dapur123") {
        username = user;
        role = "Dapur";
        accept();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}
