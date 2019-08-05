#ifndef SEARCHINFOLESSONS_H
#define SEARCHINFOLESSONS_H

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
#include <QMapIterator>
#include <QMovie>


namespace Ui {
class searchInfoLessons;
}

class searchInfoLessons : public QWidget
{
    Q_OBJECT

public:
    explicit searchInfoLessons(QWidget *parent = nullptr);
    ~searchInfoLessons();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();


private:
    Ui::searchInfoLessons *ui;
    QSqlTableModel *model_lesson;
    QString current_selected_lessonID;  //当前选择查看的课程的数据库表名
    QMap <int,int> rows_lessonsID; //行号与课程的ID的map

};

#endif // SEARCHINFOLESSONS_H
