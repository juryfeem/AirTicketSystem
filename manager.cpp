#include "manager.h"
#include "ui_manager.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QPushButton>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QSqlRecord>
#include"customerlist.h"

int id3;
QSqlTableModel *model_3;
QSqlDatabase Db;
QSqlRecord record_3;
QPushButton *btn_chose_2;

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    Db = QSqlDatabase::addDatabase("QMYSQL");

    Db.setHostName("127.0.0.1");
    Db.setUserName("root");
    Db.setPassword("root");
    Db.setDatabaseName("airticketsystem");

    if(!Db.open()){
        QMessageBox::warning(this,"警告",Db.lastError().text());
    }

    setFixedSize(1100,600);
    model_3 = new QSqlTableModel(this);
    ui->tableView->setModel(model_3);
    model_3->setTable("airline");
    model_3->select();

    model_3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_3->setHeaderData(0,Qt::Horizontal,"编号");
    model_3->setHeaderData(1,Qt::Horizontal,"终点站");
    model_3->setHeaderData(2,Qt::Horizontal,"航班号");
    model_3->setHeaderData(3,Qt::Horizontal,"飞机号");
    model_3->setHeaderData(4,Qt::Horizontal,"日期");
    model_3->setHeaderData(5,Qt::Horizontal,"乘员定额");
    model_3->setHeaderData(6,Qt::Horizontal,"余票量");
    model_3->setHeaderData(7,Qt::Horizontal,"操作");
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setFixedSize(1100,600);
    ui->tableView->move(0,0);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;

    for(int i = ui->tableView->model()->rowCount();i > 0;i--){
        QPushButton *btn = new QPushButton("查看乘客信息");
        ui->tableView->setIndexWidget(model_3->index(i-1,7),btn);
        QSqlQuery query;

        connect(btn,&QPushButton::clicked,[&](){
            QModelIndex index = ui->tableView->selectionModel()->currentIndex();
            record_3 = model_3->record(index.row());
            id3 = record_3.value(0).toInt();
            btn_chose_2 = (QPushButton*)ui->tableView->indexWidget(index);
            CustomerList *list = new CustomerList;
            list->show();
        });
    }

}

Manager::~Manager()
{
    delete ui;
}
