#include "orderpage.h"

orderpage::orderpage()
{
    orders = new QScrollArea();
    orderitems = new QWidget();

    layoutitems = new QVBoxLayout();
    scrollspacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);

    layoutitems->addWidget(new orderpageitem());
    layoutitems->addSpacerItem(scrollspacer);

    orderitems->setLayout(layoutitems);

    orders->setWidget(orderitems);
    orders->setWidgetResizable(true);
    orders->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    mainlayout = new QVBoxLayout();
    mainlayout->addWidget(orders);

    this->setLayout(mainlayout);
}
