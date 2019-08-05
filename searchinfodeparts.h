#ifndef SEARCHINFODEPARTS_H
#define SEARCHINFODEPARTS_H

#include <QWidget>
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
class searchinfodeparts;
}

class searchinfodeparts : public QWidget
{
    Q_OBJECT

public:
    explicit searchinfodeparts(QWidget *parent = nullptr);
    ~searchinfodeparts();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::searchinfodeparts *ui;
    QSqlTableModel *model;
};

#endif // SEARCHINFODEPARTS_H
