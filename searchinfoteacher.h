#ifndef SEARCHINFOTEACHER_H
#define SEARCHINFOTEACHER_H

#include <QWidget>
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
#include <QMovie>


namespace Ui {
class searchInfoTeacher;
}

class searchInfoTeacher : public QWidget
{
    Q_OBJECT

public:
    explicit searchInfoTeacher(QWidget *parent = nullptr);
    ~searchInfoTeacher();


private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::searchInfoTeacher *ui;
    QSqlTableModel *model_teacher;
    addLessonsWindow *add_lesson_teacher_window;
    QString current_selected_teacherID;   //当前选择的教师ID
    QString current_selected_teacherName;  //当前选择的教师名称
};

#endif // SEARCHINFOTEACHER_H
