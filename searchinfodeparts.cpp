#include "searchinfodeparts.h"
#include "ui_searchinfodeparts.h"

searchinfodeparts::searchinfodeparts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::searchinfodeparts)
{
    this->setFixedSize(1065,727);
    ui->setupUi(this);

    this->setWindowIcon(QIcon("image/windowLable.jpg"));
    this->setWindowTitle("系别信息");

    //设置背景图

    QMovie *movie_back = new QMovie("image/addLesson.gif");
    ui->label_3->setMovie(movie_back);
    ui->label_3->setScaledContents(true);
    movie_back->start();


    model =new QSqlTableModel;
    model->setTable("departments");
    model->select();

    ui->tableView->setModel(model);




}

searchinfodeparts::~searchinfodeparts()
{
    delete ui;
}

void searchinfodeparts::on_pushButton_8_clicked()
{
    model->setTable("departments");
    model->select();
}

void searchinfodeparts::on_pushButton_5_clicked()
{
    model->setFilter(QString("Name = '%1'").arg(ui->lineEdit_search_name->text()));
    model->select();
}

void searchinfodeparts::on_pushButton_6_clicked()
{
    model->setFilter(QObject::tr("departID = '%1'").arg(ui->lineEdit_search_number->text().toInt()));
    model->select();
}
