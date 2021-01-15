#include "orderpage.h"
#include"common.h"
#include<QDebug>
orderpage::orderpage()
{
    orders = new QScrollArea();
    orderitems = new QWidget();

    layoutitems = new QVBoxLayout();
    scrollspacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);

    //layoutitems->addWidget(new orderpageitem());
    layoutitems->addSpacerItem(scrollspacer);

    orderitems->setLayout(layoutitems);

    orders->setWidget(orderitems);
    orders->setWidgetResizable(true);
    orders->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    mainlayout = new QVBoxLayout();
    mainlayout->addWidget(orders);

    this->setLayout(mainlayout);
}
void orderpage::addorder(QString name, QString time, QString status){
    if(order_set.contains(name))return;
    //3650599367aA
    log_error("orderpage::addorder");
    //std::cout<<name.toStdString().data()<<std::endl;

    layoutitems->removeItem(scrollspacer);
    orderpageitem* neworder = (new orderpageitem())->setvalues("#"+name,time,status);
    layoutitems->addWidget(neworder);
    layoutitems->addSpacerItem(scrollspacer);

    order_set.insert(name,neworder);
    //qDebug()<<order_set;
}
void orderpage::setstatus(QString id, QString status){
    orderpageitem* target = order_set.value(id);
    if(target){
        target->setorderstatus(status);
    }
}
