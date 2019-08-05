#include "searchinfolessons.h"
#include "ui_searchinfolessons.h"

searchInfoLessons::searchInfoLessons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchInfoLessons)
{
    this->setFixedSize(1065,727);
    ui->setupUi(this);

    this->setWindowIcon(QIcon("image/windowLable.jpg"));
    this->setWindowTitle("课程信息");

    //设置背景图

    QMovie *movie_back = new QMovie("image/addLesson.gif");
    ui->label_3->setMovie(movie_back);
    ui->label_3->setScaledContents(true);
    movie_back->start();




    model_lesson = new QSqlTableModel;
    model_lesson->setTable("lessons");
    model_lesson->setEditStrategy(QSqlTableModel::OnManualSubmit);


    ui->tableView->setModel(model_lesson);



    //添加系别信息到combox

    ui->comboBox_depart->addItem("建筑学院");
    ui->comboBox_depart->addItem("土木工程系");
    ui->comboBox_depart->addItem("建设管理系");
    ui->comboBox_depart->addItem("水利工程系");
    ui->comboBox_depart->addItem("机械工程系");
    ui->comboBox_depart->addItem("自动化系");
    ui->comboBox_depart->addItem("电子工程系");
    ui->comboBox_depart->addItem("计算机科学与技术系");
    ui->comboBox_depart->addItem("物理系");
    ui->comboBox_depart->addItem("数学系");
    ui->comboBox_depart->addItem("化学系");

}

searchInfoLessons::~searchInfoLessons()
{
    delete ui;
}

void searchInfoLessons::on_pushButton_clicked()
{
    //事务操作
    model_lesson->database().transaction();
    if(model_lesson->submitAll())
    {
        model_lesson->database().commit();
        QMessageBox::warning(this,tr("change"),tr("修改已被提交!"));

        if(model_lesson->tableName() == "lessons")
        {
          //创建一个lesson表记录选择此课的人
          QSqlQuery query;
          QString ID_;
          for(int i=0;i<model_lesson->rowCount();i++)
          {
              ID_ = ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toString();
              query.exec(QString("CREATE TABLE '%1'(ID INT PRIMARY KEY NOT NULL, grades VCHAR)").arg("LESSONS"+ID_));
          }
        }
    }
    else
    {
        model_lesson->database().rollback();
        QMessageBox::warning(this,tr("tableModel"),tr("数据库错误! %1").arg(model_lesson->database().lastError().text()));
    }
}

void searchInfoLessons::on_pushButton_2_clicked()
{
    this->model_lesson->revertAll();
}

void searchInfoLessons::on_pushButton_8_clicked()
{
    model_lesson->setTable("lessons");
    model_lesson->select();
}

void searchInfoLessons::on_pushButton_3_clicked()
{

    int rows = model_lesson->rowCount();
    int id = -1;
    model_lesson->insertRow(rows);
    model_lesson->setData(model_lesson->index(rows,0),id);


}

void searchInfoLessons::on_pushButton_4_clicked()
{
    int selected_row = ui->tableView->currentIndex().row();
    model_lesson->removeRow(selected_row);

    int is_delete = QMessageBox::warning(this,tr("删除"),tr("你确定删除当前行?"),QMessageBox::Yes,QMessageBox::No);
    if(is_delete == QMessageBox::Yes)
    {
        model_lesson->submitAll();
    }
    else {
        model_lesson->revertAll();
    }
}

void searchInfoLessons::on_pushButton_5_clicked()
{
    model_lesson->setFilter(QString("Name = '%1'").arg(ui->lineEdit_search_name->text()));
    model_lesson->select();
}

void searchInfoLessons::on_pushButton_6_clicked()
{
    model_lesson->setFilter(QObject::tr("courseID = '%1'").arg(ui->lineEdit_search_number->text().toInt()));
    model_lesson->select();
}

void searchInfoLessons::on_pushButton_7_clicked()
{
    if(model_lesson->tableName() == "lessons")
    {
       //提取所选课程的编号
       QSqlQuery query_getID;
       query_getID.exec("SELECT * FROM lessons");
       query_getID.seek(ui->tableView->currentIndex().row());

       this->current_selected_lessonID = "LESSONS"+query_getID.value(0).toString();


       //打开此课程的选课人数记录
       model_lesson->setTable(this->current_selected_lessonID);
       model_lesson->setEditStrategy(QSqlTableModel::OnManualSubmit);
       model_lesson->select();
       ui->tableView->setModel(model_lesson);


       //计算平均分
       query_getID.exec(QString("SELECT * FROM '%1'").arg(this->current_selected_lessonID));
       query_getID.first();

       double sum_score=0;
       for(int i=0;i<model_lesson->rowCount();i++)
       {
           sum_score = sum_score + query_getID.value(1).toDouble();
           query_getID.next();
       }

       double average_score = sum_score/model_lesson->rowCount();

       ui->lineEdit_average->setReadOnly(false);
       ui->lineEdit_average->setText(QString::number(average_score));
       ui->lineEdit_average->setReadOnly(true);
    }
    else
    {
        QMessageBox::warning(this,tr("failed"),tr("请选择课程!"));
    }

}









void searchInfoLessons::on_pushButton_9_clicked()
{
    QSqlQuery query;

    //获得总课程数
    model_lesson->setTable("lessons");
    model_lesson->select();
    int all_lessons = model_lesson->rowCount();



    //将课程选课情况表格转换为map
    QMap <QString,QString> *id_grades =new QMap<QString,QString>[all_lessons];

    //更新行号到课程号的哈希表
    query.exec("SELECT * FROM lessons");
    rows_lessonsID.clear();
    for(int i=0;i<all_lessons;i++)
    {
        query.seek(i);
        rows_lessonsID.insert(i,query.value(0).toInt());
    }

     //将所有课的成绩写入哈希表里

    QSqlTableModel model_getnumber;
    for(int i=0;i<all_lessons;i++)
    {

       query.exec(QString("SELECT * FROM '%1'").arg("LESSONS"+QString::number(rows_lessonsID[i])));
       query.first();

       //获取当前选课表的行数
       model_getnumber.setTable("LESSONS"+QString::number(rows_lessonsID[i]));
       model_getnumber.select();
       int currenttable_StudentNumber=model_getnumber.rowCount();


       for(int j=0;j<currenttable_StudentNumber;j++)
       {
           id_grades[i].insert(query.value(0).toString(),query.value(1).toString());
           qDebug()<<query.value(0).toString()<<query.value(1).toString();
           query.next();
       }
    }

    for(int i=0;i<all_lessons;i++)
    {

        QMap<QString,QString>::iterator _traversing;
        _traversing=id_grades[i].begin();
        while(_traversing!=id_grades[i].end())
        {
            //写入学生的课表
            query.exec(QString("UPDATE '%1' SET grades='%2' WHERE courseID='%3' ")
                    .arg("IDNAMESTUDENT"+_traversing.key())
                    .arg(_traversing.value())
                    .arg(QString::number(rows_lessonsID[i])));

            qDebug()<<rows_lessonsID[i]<<_traversing.key()<<_traversing.value();
            _traversing++;
        }
    }

}




void searchInfoLessons::on_pushButton_13_clicked()
{
    if(model_lesson->tableName()!="lessons")
    {
        model_lesson->sort(1,Qt::DescendingOrder);
        model_lesson->select();
    }
    else {
        QMessageBox::warning(this,tr("failed"),tr("当前表格错误!"));
    }
}





void searchInfoLessons::on_pushButton_12_clicked()
{
    model_lesson->setFilter(QObject::tr("Depart = '%1'").arg(ui->comboBox_depart->currentText()));
    model_lesson->select();
}




