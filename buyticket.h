#ifndef BUYTICKET_H
#define BUYTICKET_H

#include <QMainWindow>

namespace Ui {
class BuyTicket;
}

class BuyTicket : public QMainWindow
{
    Q_OBJECT

public:
    explicit BuyTicket(QWidget *parent = nullptr);
    ~BuyTicket();

public slots:
    void buy_ticket();
private:
    Ui::BuyTicket *ui;


};

#endif // BUYTICKET_H
