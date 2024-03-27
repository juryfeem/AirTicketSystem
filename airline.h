#ifndef AIRLINE_H
#define AIRLINE_H

#include <QMainWindow>
#include<QSqlTableModel>
#include"buyticket.h"

namespace Ui {
class AirLine;
}

class AirLine : public QMainWindow
{
    Q_OBJECT

public:
    explicit AirLine(QWidget *parent = nullptr);
    ~AirLine();

private:
    Ui::AirLine *ui;

    BuyTicket *bt = NULL;
};

#endif // AIRLINE_H
