#ifndef SEARCHINFOSTUDENT_H
#define SEARCHINFOSTUDENT_H

#include <addlessonswindow.h>


#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QModelIndex>
#include <QMovie>



namespace Ui {
class searchInfoStudent;
}

class searchInfoStudent : public QWidget
{
    Q_OBJECT

public:
    explicit searchInfoStudent(QWidget *parent = nullptr);
    ~searchInfoStudent();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::searchInfoStudent *ui;
    QSqlTableModel *model;
    addLessonsWindow *add_lesson_student;
    QString current_select_studentID_add; //当前选择查看的学生的数据库表名
    QMap <int,int> rows_studentID;    //当前行号与当前行学生的ID的哈希表（排序后与数据库表有可能不同）
};

#endif // SEARCHINFOSTUDENT_H
