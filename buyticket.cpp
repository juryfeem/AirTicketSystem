#include "buyticket.h"
#include "ui_buyticket.h"
#include<QSpinBox>
#include<QSqlQuery>
#include<QRadioButton>
#include<QDebug>
#include<QSqlTableModel>

extern QString name;
extern QString idNumber;
extern QString phoneNumber;
extern int id1;
extern QSqlTableModel *model;
extern QPushButton* btn_chose;
extern int ticketsleft;
extern QSqlDatabase db;
int class_num_1 = 1;


BuyTicket::BuyTicket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BuyTicket)
{
    ui->setupUi(this);
    this->setFixedSize(474,305);
    this->setWindowTitle("订单创建");




//    extern QPushButton *button_1;
//    extern QPushButton *button_2;

    ui->spinBox->setValue(1);
    ui->spinBox->setMinimum(1);
    QSqlQuery query(db);
    query.exec(QString("select ticketsLeft from airline where id = %1").arg(id1));
    if(query.next()){
        ui->spinBox->setMaximum(query.value(0).toInt());
    }


    ui->radioButton->setChecked(true);
    connect(ui->radioButton,&QRadioButton::clicked,[&](){
        class_num_1 = 1;
    });
    connect(ui->radioButton_2,&QRadioButton::clicked,[&](){
        class_num_1 = 2;
    });
    connect(ui->radioButton_3,&QRadioButton::clicked,[&](){
        class_num_1 = 3;
    });

    connect(ui->pushButton,&QPushButton::clicked,this,&BuyTicket::buy_ticket);
//        query.exec(QString("select * from customer where name = %1,airline_id = %2,idNumber = %3,phoneNumber = %4,class = %5").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num));
//        if(query.next()){
//            query.exec(QString("update customer set ticketNumber = ticketNumber + %1").arg(ui->spinBox->value()));
//        }else{
//            query.exec(QString("insert into customer(name,airline_id,idNumber,phoneNumber,class,ticketNumber) values('%1',%2,'%3','%4',%5,%6)").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num).arg(ui->spinBox->value()));
//            }

//        query.exec(QString("update airline set ticketsLeft = ticketsLeft -%1 where id = %2").arg(ui->spinBox->value()).arg(id1));

//        if(ticketsleft == ui->spinBox->value()){
//            btn_chose->setEnabled(false);
//        }
//        model->setData(model->index(id1-1,6),query.value(0));

//    this->hide();


//        query.exec(QString("select ticketsLeft from customer where name = %1,airline_id = %2,idNumber = %3,phoneNumber = %4,class = %5").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num));
//        if(query.next()){
//            query.exec(QString("update customer set ticketNumber = ticketNumber + %1").arg(ui->spinBox->value()));
//        }else{
//            query.exec(QString("insert into customer(name,airline_id,idNumber,phoneNumber,class,ticketNumber) values('%1',%2,'%3','%4',%5,%6)").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num).arg(ui->spinBox->value()));
//        }
//        query.exec(QString("update airline set ticketsLeft = ticketsLeft -%1 where id = %2").arg(ui->spinBox->value()).arg(id1));

//        query.exec(QString("select ticketsLeft from airline where id = %1").arg(id1));
//        if(query.next()){
//            model->setData(model->index(id1-1,6),query.value(0));
//            if(query.value(0).toInt() == 0){
//                switch(id1){
//                case 1:button_1->setEnabled(false);break;
//                case 2:button_2->setEnabled(false);break;
//                default:break;
//                }


//            }
//        }


    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        this->hide();
    });
}

void BuyTicket::buy_ticket(){
    QSqlQuery query(db);
    query.exec(QString("select * from customer where name = '%1' and airline_id = %2 and idNumber = '%3' and phoneNumber = '%4' and class = %5").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num_1));
    if(query.next()){
        query.exec(QString("update customer set ticketNumber = ticketNumber + %1 where name = '%2' and airline_id = %3 and idNumber = '%4' and phoneNumber = '%5' and class = %6").arg(ui->spinBox->value()).arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num_1));
    }else{
        query.exec(QString("insert into customer(name,airline_id,idNumber,phoneNumber,class,ticketNumber) values('%1',%2,'%3','%4',%5,%6)").arg(name).arg(id1).arg(idNumber).arg(phoneNumber).arg(class_num_1).arg(ui->spinBox->value()));
        }

    query.exec(QString("update airline set ticketsLeft = ticketsLeft -%1 where id = %2").arg(ui->spinBox->value()).arg(id1));

    if(ticketsleft == ui->spinBox->value()){
        btn_chose->setEnabled(false);
    }
    model->setData(model->index(id1-1,6),ticketsleft - ui->spinBox->value());

    this->hide();
}

BuyTicket::~BuyTicket()
{
    delete ui;
}
