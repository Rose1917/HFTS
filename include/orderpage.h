#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include<QWidget>
#include<QScrollArea>
#include"orderpageitem.h"
class orderpage : public QWidget
{
    Q_OBJECT
public:
    orderpage();
private:
    QMap<QString,orderpageitem*> order_set;
    QScrollArea* orders;
    QWidget* orderitems;
    QVBoxLayout* layoutitems;
    QSpacerItem* scrollspacer;
    QVBoxLayout* mainlayout;
private slots:
    void addorder(QString id,QString time,QString status);
    void setstatus(QString id,QString status);
};

#endif // ORDERPAGE_H
