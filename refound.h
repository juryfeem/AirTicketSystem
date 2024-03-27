#ifndef REFOUND_H
#define REFOUND_H

#include <QWidget>
#include<QTableView>

namespace Ui {
class Refound;
}

class Refound : public QWidget
{
    Q_OBJECT

public:
    explicit Refound(QWidget *parent = nullptr);
    ~Refound();

public slots:
    void confirm_change();
    //void receive_tableview(QTableView *tableview_1);

private:
    Ui::Refound *ui;
};

#endif // REFOUND_H
