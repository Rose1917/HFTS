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
    QScrollArea* orders;
    QWidget* orderitems;
    QVBoxLayout* layoutitems;
    QSpacerItem* scrollspacer;
    QVBoxLayout* mainlayout;
};

#endif // ORDERPAGE_H
