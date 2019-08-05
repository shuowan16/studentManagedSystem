#include "mainwindow.h"
#include <QApplication>
#include "welcomewindow.h"
#include <public_fuctions.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    createConnection();


    WelcomeWindow *login;
    login = new WelcomeWindow;


    login->setWindowIcon(QIcon("image/windowLable.jpg"));
    login->setWindowTitle("成绩管理系统登录");
    login->show();



    //登录成功后显示主界面
    QObject::connect(login,&WelcomeWindow::succeed_login,&login->w,&MainWindow::show);
    return a.exec();

}
