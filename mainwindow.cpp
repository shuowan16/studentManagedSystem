#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    this->setFixedSize(1065,727);
    ui->setupUi(this);
    this->setWindowIcon(QIcon("image/windowLable.jpg"));
    this->setWindowTitle("成绩管理系统");




    this->thread_voice = new QThread;   //开辟一个新的线程
    this->voice_to_read = new voice_operation;  //实例化播报对象
    this->voice_to_read->moveToThread(this->thread_voice);  //对象进入线程执行

    QObject::connect(this,&MainWindow::start_voice_thread,voice_to_read,&voice_operation::WordsToSay);
    QObject::connect(thread_voice,&QThread::finished,voice_to_read,&QObject::deleteLater);  //线程结束后销毁对象

    thread_voice->start();
    emit this->start_voice_thread();


    //设置主界面动画

    QMovie *new_movie_bug = new QMovie("image/depart.gif");
    ui->label_picture->setMovie(new_movie_bug);
    ui->label_picture->setScaledContents(true);
    new_movie_bug->start();



    //联系QQ
    QObject::connect(ui->action3463877866_qq_com,&QAction::triggered,
                     [=]()
    {
        QDesktopServices::openUrl((QString)"https://mail.qq.com/");
    });

    //查看代码
    QObject::connect(ui->action,&QAction::triggered,
                     [=]()
    {
        QDesktopServices::openUrl((QString)"https://github.com/shuowan16/studentManagedSystem");
    });


    //查询学生信息



    QObject::connect(ui->action_search_student_info,&QAction::triggered,
                     [=]()
    {
        this->search_studentInfo_window.show();
    });



    //查询课程信息



    QObject::connect(ui->action_lesson,&QAction::triggered,
                     [=]()
    {
        this->search_lessonInfo_window.show();
    });




    //查询教师信息



    QObject::connect(ui->action_teacher,&QAction::triggered,
                     [=]()
    {
        this->search_teacherInfo_window.show();
    });


    //查询系别信息
    QObject::connect(ui->action_depart,&QAction::triggered,
                     [=]()
    {
        this->search_departInfo_window.show();
    });



}

MainWindow::~MainWindow()
{
    delete ui;
}
