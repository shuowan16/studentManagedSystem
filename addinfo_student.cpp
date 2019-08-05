#include "addinfo_student.h"
#include "ui_addinfo_student.h"


addinfo_student::addinfo_student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addinfo_student)
{
    ui->setupUi(this);

    //退出按钮
    QObject::connect(ui->action_exit,&QAction::triggered,
                     [=]()
    {
        this->close();
    });

    //保存按钮
    QObject::connect(ui->action_save,&QAction::triggered,
                     [=]()
    {
        int _number = ui->lineEdit_numberinput->text().toInt();
        QString _name = ui->lineEdit_nameinput->text();
        QString _depart = ui->comboBox_depart->currentText();
        QString _grade = ui->comboBox_grade->currentText();


        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

        QSqlQuery query(db);

        qDebug()<<query.exec("INSERT INTO student ('学号', '姓名', '系别', '年级','总绩点') "
                         "VALUES (_number, _name, _depart, _grade, 0.00)");

        db.close();
        this->close();

    });

}

addinfo_student::~addinfo_student()
{
    delete ui;
}
