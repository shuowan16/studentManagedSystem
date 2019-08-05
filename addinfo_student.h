#ifndef ADDINFO_STUDENT_H
#define ADDINFO_STUDENT_H

#include <QMainWindow>
#include <QFile>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableView>
#include <QDebug>

namespace Ui {
class addinfo_student;
}

class addinfo_student : public QMainWindow
{
    Q_OBJECT

public:
    explicit addinfo_student(QWidget *parent = nullptr);
    ~addinfo_student();

private:
    Ui::addinfo_student *ui;
};

#endif // ADDINFO_STUDENT_H
