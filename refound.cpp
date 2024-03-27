#include "refound.h"
#include "ui_refound.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlRecord>
#include"orderform.h"
#include"airline.h"


//QTableView *tableview;

Refound::Refound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Refound)
{
    ui->setupUi(this);
    this->setFixedSize(474,305);

    extern int class_num;
    extern QString name;
    extern QString idNumber;
    extern QString phoneNumber;
    extern int id2;
    extern QSqlQueryModel *model_2;
    extern QSqlDatabase db;
    extern int tickets;

    QSqlQuery query(db);

    //qDebug()<< class_num<<id2;

    this->setWindowTitle("退票申请");



    //query.exec(QString("selcet ticketNumber from customer where name = %1,airline_id = %2,idNumber = %3,phoneNumber = %4,class = %5").arg(name).arg(id2).arg(idNumber).arg(phoneNumber).arg(class_num));

    //qDebug() << query.exec("select * from customer");


    ui->spinBox->setMaximum(tickets);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setValue(1);

    connect(ui->pushButton,&QPushButton::clicked,this,[&](){
        this->hide();
    });

//    connect(ui->pushButton_2,&QPushButton::clicked,this,[&](){
//        qDebug() << query.exec("select * from customer");
//        if(ui->spinBox->value() == tickets){
//            query.exec(QString("delete from customer where name = '%1' and airline_id = %2 and idNumber = '%3' and phoneNumber = '%4' and class = %5").arg(name).arg(id2).arg(idNumber).arg(phoneNumber).arg(class_num));
//        }else{
//            //query.exec(QString("update customer set ticketNumber = ticketNumber - %1 where name = '%2' and airline_id = %3 and idNumber = '%4' and phoneNumber = '%5' and class = %6").arg(ui->spinBox->value()).arg(name).arg(id2).arg(idNumber).arg(phoneNumber).arg(class_num));
//            qDebug() << query.exec("select * from customer");
//        }
//        this->hide();
//    });

    connect(ui->pushButton_2,&QPushButton::clicked,this,&Refound::confirm_change);
}

//void Refound::receive_tableview(QTableView *tableview_1){
//    tableview = tableview_1;

//}

void Refound::confirm_change(){
    extern int class_num;
    extern QString name;
    extern QString idNumber;
    extern QString phoneNumber;
    extern int id2;
    extern QSqlQueryModel *model_2;
    extern QSqlDatabase db;
    extern int tickets;
    extern OrderForm *orders;
    extern AirLine *al;

    QSqlQuery query(db);
    if(ui->spinBox->value() == tickets){
        query.exec(QString("delete from customer where name = '%1' and airline_id = %2 and idNumber = '%3' and phoneNumber = '%4' and class = %5").arg(name).arg(id2).arg(idNumber).arg(phoneNumber).arg(class_num));
    }else{
        query.exec(QString("update customer set ticketNumber = ticketNumber - %1 where name = '%2' and airline_id = %3 and idNumber = '%4' and phoneNumber = '%5' and class = %6").arg(ui->spinBox->value()).arg(name).arg(id2).arg(idNumber).arg(phoneNumber).arg(class_num));
    }
    query.exec(QString("update airline set ticketsLeft = ticketsLeft + %1 where id = %2").arg(ui->spinBox->value()).arg(id2));
    this->hide();

    al->close();
    al = new AirLine;
    al->show();
    orders->close();
    orders = new OrderForm;
    orders->show();


}

Refound::~Refound()
{
    delete ui;
}
