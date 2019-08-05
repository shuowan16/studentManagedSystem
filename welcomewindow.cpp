#include "welcomewindow.h"
#include "ui_welcomewindow.h"


WelcomeWindow::WelcomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

    //固定窗口大小
    this->setFixedSize(500,500);

    //设置背景
    ui->widget_background->setAutoFillBackground(true);
    QPalette palette_background;
    palette_background.setBrush(QPalette::Window,QBrush(QPixmap("image/background.jpg").scaled(
                                                            this->size(),
                                                            Qt::IgnoreAspectRatio,
                                                            Qt::SmoothTransformation)));
    this->setPalette(palette_background);
    ui->label->setAlignment(Qt::AlignCenter);


    ui->lineEdit_password->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    QObject::connect(ui->pushButton_rigister,&QPushButton::clicked,
                     [=]()
    {
        QMessageBox dialog_rigister;
        dialog_rigister.setText("rigister succeed!");
        dialog_rigister.setWindowTitle("注册");
        dialog_rigister.setFixedSize(300,100);
        dialog_rigister.exec();
        this->dealRigster();

    });

    //登录
    QObject::connect(ui->pushButton_login,&QPushButton::clicked,
                     [=]()
    {
          this->dealLogin();
    });


}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::dealRigster()
{
    this->current_rigister_name=ui->lineEdit_username->text();
    this->current_rigister_password=ui->lineEdit_password->text();



    QFile file_new("usersfile/"+ui->lineEdit_username->text());
    file_new.open(QIODevice::WriteOnly);
    QTextStream stream_new(&file_new);
    stream_new<<ui->lineEdit_password->text();
    file_new.close();
}

void WelcomeWindow::dealLogin()
{
    this->current_login_name = ui->lineEdit_username->text();
    this->current_login_password = ui->lineEdit_password->text();


    QFile file_login("usersfile/"+ui->lineEdit_username->text());
    bool isOk = file_login.open(QIODevice::ReadOnly);
    if(true == isOk)
    {
        QTextStream stream_login(&file_login);
        QString _name;
        _name=stream_login.readLine();

        if(this->current_login_password == _name)
        {
            emit succeed_login();
            this->close();
        }
        else
        {
            QMessageBox dialog_login;
            dialog_login.setText("password failed");
            dialog_login.setWindowTitle("login");
            dialog_login.setFixedSize(300,100);
            dialog_login.exec();
        }
    }
    else
    {
        QMessageBox dialog_login;

        dialog_login.setText("user name failed");
        dialog_login.setWindowTitle("login");
        dialog_login.setFixedSize(300,100);
        dialog_login.exec();
    }
}

