#ifndef ADDLESSONSWINDOW_H
#define ADDLESSONSWINDOW_H

#include <QWidget>
#include <QMovie>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
namespace Ui {
class addLessonsWindow;
}

class addLessonsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit addLessonsWindow(QWidget *parent = nullptr);
    ~addLessonsWindow();

    void setSourceTableName(QString _name);              //传入调用者table的名字，是老师还是学生  QString tabelName
    void setcurrent_openTableName(const QString &_ID);  //传入数据库表名     QString currentStudentID

    void setcurrentStudentNumber(const QString _number); //设置添加课程学生学号    QString currentStudent_number
    void setcurrentTeacherName(QString _name);          //设置添加课程的老师名字   QString currentTeacherName


    void update_combox();                               //更新combox

private slots:
    void on_pushButton_clicked();

    bool on_pushButton_2_clicked();


    //添加完信息后给课程信息一个反馈
    void feedbackTOlessonsTable(QString _lessonID);

private:
    Ui::addLessonsWindow *ui;

    QString source_tabelName;
    QString current_openTableName;//数据表名
    QString currentStudent_number;//学号

    QString currentTeacherName;//教师名字
    QSqlTableModel *model_add_lesson;
    int all_rows_lessons;//总课程数
};

#endif // ADDLESSONSWINDOW_H
