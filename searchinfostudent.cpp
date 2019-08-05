#include "searchinfostudent.h"
#include "ui_searchinfostudent.h"
#include "public_fuctions.h"
searchInfoStudent::searchInfoStudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchInfoStudent)
{
    this->setFixedSize(1065,727);
    ui->setupUi(this);
    this->setWindowIcon(QIcon("image/windowLable.jpg"));
    this->setWindowTitle("学生信息");

    //设置背景图

    QMovie *movie_back = new QMovie("image/addLesson.gif");
    ui->label_3->setMovie(movie_back);
    ui->label_3->setScaledContents(true);
    movie_back->start();


    model = new QSqlTableModel;
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    ui->tableView->setModel(model);


    //将系别写入combox_depart

    ui->comboBox_depart->addItem("建筑学院");
    ui->comboBox_depart->addItem("土木工程系");
    ui->comboBox_depart->addItem("建设管理系");
    ui->comboBox_depart->addItem("水利工程系");
    ui->comboBox_depart->addItem("机械工程系");
    ui->comboBox_depart->addItem("电子工程系");
    ui->comboBox_depart->addItem("自动化系");
    ui->comboBox_depart->addItem("计算机科学与技术系");
    ui->comboBox_depart->addItem("物理系");
    ui->comboBox_depart->addItem("数学系");
    ui->comboBox_depart->addItem("化学系");




}

searchInfoStudent::~searchInfoStudent()
{
    delete ui;
}

void searchInfoStudent::on_pushButton_clicked()
{
    //事务操作
    model->database().transaction();
    if(model->submitAll())
    {
        model->database().commit();
        QMessageBox::warning(this,tr("change"),tr("修改已被提交!"));
    }
    else
    {
        model->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),tr("数据库错误! %1").arg(model->database().lastError().text()));
    }
}



void searchInfoStudent::on_pushButton_2_clicked()
{
    model->revertAll();
}

void searchInfoStudent::on_pushButton_5_clicked()
{
    model->setFilter(QString("Name = '%1'").arg(ui->lineEdit_search_name->text()));
    model->select();
}
void searchInfoStudent::on_pushButton_6_clicked()
{
    model->setFilter(QObject::tr("ID = '%1'").arg(ui->lineEdit_search_number->text().toInt()));
    model->select();
}

void searchInfoStudent::on_pushButton_8_clicked()
{
    model->setTable("student");
    model->select();
}

void searchInfoStudent::on_pushButton_3_clicked()
{
    int rows = model->rowCount();
    int id = -1;
    model->insertRow(rows);
    model->setData(model->index(rows,0),id);
}

void searchInfoStudent::on_pushButton_4_clicked()
{
    int selected_row = ui->tableView->currentIndex().row();//获取当前选择的行号


    int is_delete = QMessageBox::warning(this,tr("删除"),tr("你确定删除当前行?"),QMessageBox::Yes,QMessageBox::No);
    if(is_delete == QMessageBox::Yes)
    {

        //如果删除的是学生，则需要将与之关联的其他信息也删除
        if(model->tableName() == "student")
        {
            //获取当前学生的ID
            QSqlQuery query;
            query.exec("SELECT * FROM student");
            query.seek(selected_row);
            QString current_selected_ID_delete = query.value(0).toString();

            //删除选课表
            query.exec(QString("DROP TABLE '%1'").arg("IDNAMESTUDENT"+current_selected_ID_delete));
        }

        //提交
        model->removeRow(selected_row);
        model->submitAll();
    }
    else {
        //撤回
        model->revertAll();
    }

}



void searchInfoStudent::on_pushButton_7_clicked()
{
    if(model->tableName() == "student")

    {//提取所选行学生的学号
     QModelIndex current_index=model->index(ui->tableView->currentIndex().row(),0);


     QString current_select_ID = model->data(current_index).toString();

     qDebug()<<current_select_ID;


    //创建以学生学号命名的数据库表，学号作为唯一标识
    QSqlQuery query_add;
    query_add.exec(QString("CREATE TABLE '%1'(courseID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
               "courseDepart VCHAR, Credit VCHAR, grades VCHAR)").arg("IDNAMESTUDENT"+current_select_ID));

    //关闭添加课程窗口时自动销毁
    this->add_lesson_student = new addLessonsWindow;
    add_lesson_student->setAttribute(Qt::WA_DeleteOnClose, true);



    this->add_lesson_student->setcurrent_openTableName("IDNAMESTUDENT"+current_select_ID);
    this->add_lesson_student->setcurrentStudentNumber(current_select_ID);
    this->add_lesson_student->setSourceTableName("student");


    this->add_lesson_student->update_combox();
    this->add_lesson_student->show();
    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("请选择学生!"));
    }

}


void searchInfoStudent::on_pushButton_12_clicked()
{
    if(model->tableName() == "student")
    {
       //提取所选行学生的学号
        QModelIndex current_index=model->index(ui->tableView->currentIndex().row(),0);


       this->current_select_studentID_add = model->data(current_index).toString();


       //打开该学生所选课的数据库表
       model->setTable("IDNAMESTUDENT"+this->current_select_studentID_add);
       model->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model->select();
       ui->tableView->setModel(model);
    }
    else
    {
        QMessageBox::warning(this,tr("failed"),tr("请选择学生!"));
    }

}

void searchInfoStudent::on_pushButton_13_clicked()
{
    model->setTable("student");
    model->select();

    QModelIndex *index_tofindID = new QModelIndex;

    QSqlQuery query_student;
    query_student.exec("SELECT * FROM student");

    //更新map
    this->rows_studentID.clear();
    for(int i=0;i<this->model->rowCount();i++)
    {
        *index_tofindID = model->index(i,0);
        this->rows_studentID.insert(i,model->data(*index_tofindID).toInt()); //插入map
    }


    for(int i=0;i<model->rowCount();i++)
    {
       double test = getGPA_singleStudent(QString("IDNAMESTUDENT"+QString::number(this->rows_studentID[i])));
       query_student.exec(QString("UPDATE student SET GPA='%1' WHERE ID=='%2'").arg(test).arg(QString::number(this->rows_studentID[i])));

    }


}




void searchInfoStudent::on_pushButton_14_clicked()
{

    if(model->tableName() == "student")
    {
        model->sort(0, Qt::AscendingOrder);
        model->select();
    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("当前表格错误!"));
    }
}




void searchInfoStudent::on_pushButton_15_clicked()
{
    if(model->tableName() == "student")
    {
        model->sort(4, Qt::DescendingOrder);
        model->select();
    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("当前表格错误!"));
    }
}





void searchInfoStudent::on_pushButton_9_clicked()
{
    model->setFilter(QObject::tr("Depart = '%1'").arg(ui->comboBox_depart->currentText()));
    model->select();
}
