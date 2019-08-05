#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <searchinfostudent.h>
#include <searchinfolessons.h>
#include <searchinfoteacher.h>
#include <searchinfodeparts.h>
#include <voice_operation.h>

#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMovie>
#include <QThread>
#include <QDesktopServices>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


signals:
    void start_voice_thread();

private:
    Ui::MainWindow *ui;
    searchInfoStudent search_studentInfo_window;
    searchInfoLessons search_lessonInfo_window;
    searchInfoTeacher search_teacherInfo_window;
    searchinfodeparts search_departInfo_window;

    voice_operation *voice_to_read;
    QThread *thread_voice;

};

#endif // MAINWINDOW_H
