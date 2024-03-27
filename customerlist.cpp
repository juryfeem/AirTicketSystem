#include "customerlist.h"
#include "qsqlquerymodel.h"
#include "ui_customerlist.h"
#include<QSqlQuery>
#include<QSqlQueryModel>

CustomerList::CustomerList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerList)
{
    ui->setupUi(this);

    extern int id3;

    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setFixedSize(550,500);
    this->setWindowTitle("乘客名单");
    QSqlQueryModel *model_4 = new QSqlQueryModel(ui->tableView);
    model_4->setQuery(QString("select name,idNumber,phoneNumber,class,ticketNumber from customer where airline_id = %1").arg(id3));
    ui->tableView->setModel(model_4);

    model_4->setHeaderData(0,Qt::Horizontal,"姓名");
    model_4->setHeaderData(1,Qt::Horizontal,"身份证号");
    model_4->setHeaderData(2,Qt::Horizontal,"手机号");
    model_4->setHeaderData(3,Qt::Horizontal,"舱位等级");
    model_4->setHeaderData(4,Qt::Horizontal,"购票数");

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setFixedSize(550,500);
    ui->tableView->move(0,0);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

CustomerList::~CustomerList()
{
    delete ui;
}
