#ifndef PUBLIC_FUCTIONS_H
#define PUBLIC_FUCTIONS_H


#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QVector>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QMap>

static bool createConnection()
{
    //打开数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("demo.db");
    db.open();

    QSqlQuery query;

    //创建数据库表
    query.exec("CREATE TABLE student(ID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "Depart VCHAR, Grade VCHAR, GPA DOUBLE)");

    query.exec("CREATE TABLE teacher(ID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "Depart VCHAR)");

    query.exec("CREATE TABLE lessons(courseID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "Depart VCHAR, Credit VCHAR,Teacher VCHAR, Address VCHAR)");

    query.exec("CREATE TABLE departments(departID INT PRIMARY KEY NOT NULL, Name VCHAR NOT NULL,"
                                     "Address VCHAR)");

    //添加系别信息

    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1000, '建筑学院', '清华大学建筑馆')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1001, '土木工程系', '何善衡楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1002, '建设管理系', '西主楼三层')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1003, '水利工程系', '新水利馆')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1004, '机械工程系', '李兆基科技大楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1005, '自动化系', '中央主楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1006, '电子工程系', '罗姆楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1007, '计算机科学与技术系', '东主楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1008, '物理系', '理科楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1008, '数学系', '理科楼')");
    query.exec("INSERT INTO departments (departID, Name, Address) "
                     "VALUES (1009, '化学系', '何添楼')");
}


static double getGPA_singleStudent( QString _database_Table_Name)
{
    int all_credits=0;        //总学分
    double  sum_creditMUTIgrades=0; //总学分乘以成绩

    QSqlTableModel model_help;

    model_help.setTable(_database_Table_Name);
    model_help.select();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM '%1'").arg(_database_Table_Name));
    query.first();

    for(int i=0;i<model_help.rowCount();i++)
    {
        if(query.value(4).toString() != "")
        {

            all_credits = all_credits +query.value(3).toInt();

            sum_creditMUTIgrades = sum_creditMUTIgrades+query.value(3).toInt()*query.value(4).toDouble();
        }
        query.next();
    }

    double new_GPA = (sum_creditMUTIgrades/all_credits)/100*4;  //GPA算法
    return new_GPA;
}




#endif // PUBLIC_FUCTIONS_H
