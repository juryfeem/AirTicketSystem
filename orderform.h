#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QMainWindow>
#include<QTableView>

namespace Ui {
class OrderForm;
}

class OrderForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderForm(QWidget *parent = nullptr);
    ~OrderForm();

//signals:
//    void send_tableview(QTableView *tableview);

private:
    Ui::OrderForm *ui;
};

#endif // ORDERFORM_H
