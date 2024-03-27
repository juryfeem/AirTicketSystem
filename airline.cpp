#include "airline.h"
#include "ui_airline.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QPushButton>
#include<QSqlQuery>
#include"orderform.h"
#include<QAction>
#include<QSqlRecord>

int id1;
QSqlTableModel *model;
//QPushButton *button_1;
//QPushButton *button_2;
QSqlDatabase db;
OrderForm *orders;
QSqlRecord record;
QPushButton *btn_chose;
int ticketsleft;

AirLine::AirLine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirLine)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose,true);

    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("airticketsystem");

    if(!db.open()){
        QMessageBox::warning(this,"警告",db.lastError().text());
    }

    setFixedSize(1200,600);
    model = new QSqlTableModel(this);
    ui->tableView->setModel(model);
    model->setTable("airline");
    model->select();

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"终点站");
    model->setHeaderData(2,Qt::Horizontal,"航班号");
    model->setHeaderData(3,Qt::Horizontal,"飞机号");
    model->setHeaderData(4,Qt::Horizontal,"日期");
    model->setHeaderData(5,Qt::Horizontal,"乘员定额");
    model->setHeaderData(6,Qt::Horizontal,"余票量");
    model->setHeaderData(7,Qt::Horizontal,"操作");
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setFixedSize(1100,600);
    ui->tableView->move(0,0);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QSqlQuery query;
    //购票按钮设置
//    button_1 = new QPushButton("购票");
//    id1 = 1;
//    query.exec(QString("select ticketsLeft from airline where id = %1").arg(id1));
//    if(query.next()){
//        if(query.value(0).toInt() == 0){
//            button_1->setEnabled(false);
//        }
//    }

//    connect(button_1, &QPushButton::clicked, this,[&](){
//        bt = new BuyTicket;
//        id1 = 1;
//        bt->show();
//    });

//    ui->tableView->setIndexWidget(model->index(0,7),button_1);


//    button_2 = new QPushButton("购票");
//    id1 = 2;
//    query.exec(QString("select ticketsLeft from airline where id = %1").arg(id1));
//    if(query.next()){
//        if(query.value(0).toInt() == 0){
//            button_2->setEnabled(false);
//        }
//    }

//    connect(button_2,  &QPushButton::clicked, this, [&](){
//        bt = new BuyTicket;
//        id1 = 2;
//        bt->show();
//    });
//    ui->tableView->setIndexWidget(model->index(1,7),button_2);

    for(int i = ui->tableView->model()->rowCount();i > 0;i--){
        QPushButton *btn = new QPushButton("购票");
        ui->tableView->setIndexWidget(model->index(i-1,7),btn);
        QSqlQuery query;
        if(model->data(model->index(i-1,6)) == 0){
            btn->setEnabled(false);
        }

        connect(btn,&QPushButton::clicked,[&](){
            QModelIndex index = ui->tableView->selectionModel()->currentIndex();
            record = model->record(index.row());
            id1 = record.value(0).toInt();
            ticketsleft = record.value(6).toInt();
            btn_chose = (QPushButton*)ui->tableView->indexWidget(index);
            //query.exec(QString("select ticketsLeft from airline where id = %1").arg(id1));
            bt = new BuyTicket;
            bt->show();
        });
    }



    //订单按钮设置
    connect(ui->action_1,&QAction::triggered,[&](){
       orders = new OrderForm;
       orders->show();
    });

}


AirLine::~AirLine()
{
    delete ui;
}
