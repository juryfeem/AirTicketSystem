#include "login.h"
#include "ui_login.h"
#include<QSqlQuery>
#include"manager.h"
#include<QMessageBox>

QString name;
QString idNumber;
QString phoneNumber;
AirLine *al;

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("登录界面");
    this->setFixedSize(474,305);

    //QSqlQuery querry;
    //querry.exec(QString("insert into customer values(%1,%2,%3)").arg(name).arg(idNumber).arg(phoneNumber));

}



Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
    name = ui->lineEdit->text();
    idNumber = ui->lineEdit_2->text();
    phoneNumber = ui->lineEdit_3->text();

    //qDebug() << name;
    al = new AirLine;
    this->hide();
    al->setWindowTitle("航班信息");
    al->show();
}


void Login::on_pushButton_2_clicked()
{
    if(((ui->lineEdit->text() == "Manager") || (ui->lineEdit->text() == "manager")) && (ui->lineEdit_2->text() == "") && (ui->lineEdit_3->text() == "")){
        Manager *management = new Manager;
        management->show();
        this->hide();
    }else{
        QMessageBox::information(this,"提示","管理员登陆失败");
    }
}

