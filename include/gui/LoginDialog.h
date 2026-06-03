#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

class LoginDialog : public QDialog {
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const { return username; }
    QString getRole() const { return role; }

private slots:
    void handleLogin();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QString username;
    QString role;
};

#endif // LOGIN_DIALOG_H
