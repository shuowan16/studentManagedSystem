#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <mainwindow.h>

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QImage>
#include <QPalette>
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class WelcomeWindow;
}

class WelcomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();
    MainWindow w;

    void dealRigster();
    void dealLogin();

    //判断是否登录成功
signals:
    void succeed_login();


private:
    Ui::WelcomeWindow *ui;
    QString current_rigister_name;
    QString current_rigister_password;
    QString current_login_name;
    QString current_login_password;

};

#endif // WELCOMEWINDOW_H
