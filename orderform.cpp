#include "orderform.h"
#include "ui_orderform.h"
#include<QSqlQueryModel>
#include<QSqlDatabase>
#include<QPushButton>
#include<QSqlQuery>
#include"refound.h"
#include<QSqlRecord>
#include<QModelIndex>
#include<QDebug>
#include<QTableView>

int class_num;
int  id2;
QSqlQueryModel *model_2;
int tickets;


OrderForm::OrderForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderForm)
{
    ui->setupUi(this);

    extern QString name;
    extern QString idNumber;
    extern QString phoneNumber;
    extern QSqlDatabase db;

    this->setWindowTitle("我的订单");
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setFixedSize(1000,500);
    model_2 = new QSqlQueryModel(ui->tableView);
    model_2->setQuery(QString("select a.id,a.destination,a.flightNumber,a.aircraftNumber,a.date,c.class,c.ticketNumber,a.pushbutton from airline a,customer c where (a.id in (select airline_id from customer where name = '%1')) && (c.name = '%1')").arg(name),db);
    ui->tableView->setModel(model_2);

    model_2->setHeaderData(0,Qt::Horizontal,"编号");
    model_2->setHeaderData(1,Qt::Horizontal,"终点站");
    model_2->setHeaderData(2,Qt::Horizontal,"航班号");
    model_2->setHeaderData(3,Qt::Horizontal,"飞机号");
    model_2->setHeaderData(4,Qt::Horizontal,"日期");
    model_2->setHeaderData(5,Qt::Horizontal,"舱位等级");
    model_2->setHeaderData(6,Qt::Horizontal,"购票数");
    model_2->setHeaderData(7,Qt::Horizontal,"操作");
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setFixedSize(1000,500);
    ui->tableView->move(0,0);
    ui->tableView->verticalHeader()->setDefaultSectionSize(60);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);



    for(int i = ui->tableView->model()->rowCount();i > 0;i--){
        QPushButton *botton = new QPushButton("退票");
        ui->tableView->setIndexWidget(model_2->index(i-1,7),botton);
        QSqlQuery query(db);

        connect(botton,&QPushButton::clicked,[&](){
            QModelIndex index = ui->tableView->selectionModel()->currentIndex();
            QSqlRecord record_2 = model_2->record(index.row());
            class_num = record_2.value(5).toInt();
            id2 = record_2.value(0).toInt();
            tickets = record_2.value(6).toInt();
            Refound *refoundPage = new Refound;
//            connect(this,&OrderForm::send_tableview(QTableView *tableview),refoundPage,&Refound::receive_tableview(QTableView *tableview_1));
//            emit send_tableview(ui->tableView);
            refoundPage->show();
        });
    }
}

OrderForm::~OrderForm()
{
    delete ui;
}
