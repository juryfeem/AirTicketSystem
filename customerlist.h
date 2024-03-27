#ifndef CUSTOMERLIST_H
#define CUSTOMERLIST_H

#include <QWidget>

namespace Ui {
class CustomerList;
}

class CustomerList : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerList(QWidget *parent = nullptr);
    ~CustomerList();

private:
    Ui::CustomerList *ui;
};

#endif // CUSTOMERLIST_H
