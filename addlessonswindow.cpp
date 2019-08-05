#include "addlessonswindow.h"
#include "ui_addlessonswindow.h"

addLessonsWindow::addLessonsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addLessonsWindow)
{

    this->setFixedSize(382,495);
    this->setWindowTitle("添加");
    this->setWindowIcon(QIcon("image/windowLable.jpg"));

    ui->setupUi(this);

    //设置界面动画
    QMovie *new_movie = new QMovie("image/addLesson.gif");
    ui->label_picture->setMovie(new_movie);
    ui->label_picture->setScaledContents(true);
    new_movie->start();



}

addLessonsWindow::~addLessonsWindow()
{
    delete ui;
}



void addLessonsWindow::setcurrent_openTableName(const QString &_ID)
{
    this->current_openTableName = _ID;
}



void addLessonsWindow::on_pushButton_clicked()
{
    QSqlQuery query2;

    query2.exec("SELECT * FROM lessons");
    query2.first();


    while(1)
    {
        if(query2.value(1).toString() == ui->comboBox_courseName->currentText())
        {
            QString _courseID = query2.value(0).toString();
            QString _Name = query2.value(1).toString();
            QString _depart = query2.value(2).toString();
            QString _credit = query2.value(3).toString();

            query2.exec(QString("INSERT INTO '%1' (courseID,Name,courseDepart,Credit) "
                             "VALUES ('%2','%3','%4','%5')").arg(this->current_openTableName).arg(_courseID)
                             .arg(_Name).arg(_depart).arg(_credit));
            this->feedbackTOlessonsTable(_courseID);
            break;
        }
        query2.next();
    }
}


void addLessonsWindow::update_combox()
{

    ui->comboBox_courseName->clear();

    //设置combox的选择
    QSqlQuery query1;
    query1.exec("SELECT * FROM lessons");
    query1.first();

    //获取lessons表的总行数
    this->model_add_lesson = new QSqlTableModel;
    model_add_lesson->setTable("lessons");
    model_add_lesson->select();
    int _allrows = model_add_lesson->rowCount();
    delete model_add_lesson;

    this->all_rows_lessons = _allrows;

    for(int i =0;i<_allrows;i++)
    {
        ui->comboBox_courseName->addItem(query1.value(1).toString());
        query1.next();
    }
}

bool addLessonsWindow::on_pushButton_2_clicked()
{


    QSqlQuery query2;

    query2.exec("SELECT * FROM lessons");
    query2.first();


    for(int i =0;i<this->all_rows_lessons;i++)
    {
        if(query2.value(0).toString() == ui->lineEdit_courseNumber->text())
        {
            query2.exec(QString("INSERT INTO '%1' (courseID,Name,courseDepart,Credit) "
                             "VALUES ('%2','%3','%4','%5')").arg(this->current_openTableName).arg(query2.value(0).toString())
                             .arg(query2.value(1).toString()).arg(query2.value(2).toString()).arg(query2.value(3).toString()));
            this->feedbackTOlessonsTable(ui->lineEdit_courseNumber->text());
            return true;
        }
        query2.next();

    }

    //如果未找到课序号，就发出警告

    QMessageBox::warning(this,tr("add lesson"),tr("未找到该课程"));


}

void addLessonsWindow::feedbackTOlessonsTable(QString _lessonID)
{


    if(this->source_tabelName == "student")
    {
      QSqlQuery query;
      query.exec(QString("INSERT INTO '%1' (ID, grades) "
                 "VALUES ('%2', '0')").arg("LESSONS"+_lessonID).arg(this->currentStudent_number));
    }



    if(this->source_tabelName == "teacher")
    {
        QSqlQuery query;
        qDebug()<<query.exec(QString("UPDATE lessons SET Teacher='%1' WHERE courseID=='%2'").arg(this->currentTeacherName).arg(_lessonID));
    }
}


void addLessonsWindow::setcurrentTeacherName(QString _name)
{
    this->currentTeacherName = _name;
}

void addLessonsWindow::setcurrentStudentNumber(const QString _number)
{
    this->currentStudent_number = _number;
}
void addLessonsWindow::setSourceTableName(QString _name)
{
    this->source_tabelName=_name;
}



