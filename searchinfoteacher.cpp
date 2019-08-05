#include "searchinfoteacher.h"
#include "ui_searchinfoteacher.h"

searchInfoTeacher::searchInfoTeacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchInfoTeacher)
{
    ui->setupUi(this);
    this->setFixedSize(1065,727);
    this->setWindowIcon(QIcon("image/windowLable.jpg"));
    this->setWindowTitle("教师信息");

    //设置背景图

    QMovie *movie_back = new QMovie("image/addLesson.gif");
    ui->label_3->setMovie(movie_back);
    ui->label_3->setScaledContents(true);
    movie_back->start();


    model_teacher = new QSqlTableModel;
    model_teacher->setTable("teacher");
    model_teacher->setEditStrategy(QSqlTableModel::OnManualSubmit);


    ui->tableView->setModel(model_teacher);


}

searchInfoTeacher::~searchInfoTeacher()
{
    delete ui;
}

void searchInfoTeacher::on_pushButton_3_clicked()
{
    int rows = model_teacher->rowCount();
    int id = -1;
    model_teacher->insertRow(rows);
    model_teacher->setData(model_teacher->index(rows,0),id);
}

void searchInfoTeacher::on_pushButton_2_clicked()
{
    model_teacher->revertAll();
}

void searchInfoTeacher::on_pushButton_clicked()
{
    //事务操作
    model_teacher->database().transaction();
    if(model_teacher->submitAll())
    {
        model_teacher->database().commit();
        QMessageBox::warning(this,tr("change"),tr("修改已被提交!"));
    }
    else
    {
        model_teacher->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),tr("数据库错误! %1").arg(model_teacher->database().lastError().text()));
    }
}

void searchInfoTeacher::on_pushButton_4_clicked()
{
    int selected_row = ui->tableView->currentIndex().row();//获取当前选择的行号


    int is_delete = QMessageBox::warning(this,tr("删除"),tr("你确定删除当前行?"),QMessageBox::Yes,QMessageBox::No);
    if(is_delete == QMessageBox::Yes)
    {


        //提交
        model_teacher->removeRow(selected_row);
        model_teacher->submitAll();
    }
    else {
        model_teacher->revertAll();
    }
}

void searchInfoTeacher::on_pushButton_5_clicked()
{
    model_teacher->setFilter(QString("Name = '%1'").arg(ui->lineEdit_search_name->text()));
    model_teacher->select();
}

void searchInfoTeacher::on_pushButton_6_clicked()
{
    model_teacher->setFilter(QObject::tr("ID = '%1'").arg(ui->lineEdit_search_number->text().toInt()));
    model_teacher->select();
}

void searchInfoTeacher::on_pushButton_8_clicked()
{
    model_teacher->setTable("teacher");
    model_teacher->select();
}

void searchInfoTeacher::on_pushButton_7_clicked()
{
    if(model_teacher->tableName() == "teacher")
    {//提取所选行教师工号

    QSqlQuery query_getID;
    query_getID.exec("SELECT ID FROM teacher");
    query_getID.seek(ui->tableView->currentIndex().row());

    QString current_select_ID = query_getID.value(0).toString();

    //创建以教师工号命名的数据库表，工号作为唯一标识
    QSqlQuery query_add;
    query_add.exec(QString("CREATE TABLE '%1'(courseID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
               "courseDepart VCHAR, Credit VCHAR, Score VCHAR)").arg("IDNAMETEACHER"+current_select_ID));


    //添加课程窗口关闭时自动销毁
    this->add_lesson_teacher_window = new addLessonsWindow;
    add_lesson_teacher_window->setAttribute(Qt::WA_DeleteOnClose, true);

    //提取当前选择教师的名字

    this->current_selected_teacherName = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString();



    this->add_lesson_teacher_window->setcurrent_openTableName("IDNAMETEACHER"+current_select_ID);
    this->add_lesson_teacher_window->setSourceTableName("teacher");
    this->add_lesson_teacher_window->setcurrentTeacherName(this->current_selected_teacherName);

    this->add_lesson_teacher_window->update_combox();
    this->add_lesson_teacher_window->show();


    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("请选择教师!"));
    }
}

void searchInfoTeacher::on_pushButton_12_clicked()
{
    if(model_teacher->tableName()=="teacher")
    {//提取所选行教师的工号
    QSqlQuery query_getID;
    query_getID.exec("SELECT ID FROM teacher");
    query_getID.seek(ui->tableView->currentIndex().row());


    this->current_selected_teacherID = query_getID.value(0).toString();

    //打开该教师所选课的数据库表
    model_teacher->setTable("IDNAMETEACHER"+this->current_selected_teacherID);
    model_teacher->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_teacher->select();

    ui->tableView->setModel(model_teacher);
    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("请选择教师!"));
    }

}


