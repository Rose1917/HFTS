#include "orderpageitem.h"

orderpageitem::orderpageitem()
{
    name = new QLabel("default");
    time = new QLabel("0000-00-00-00:00:00");

    maxinumlabel = new clickablelabel("+");
    maxinumlabel->setPixmap(QPixmap(u8":/img/添加合约.png").scaled(25,25,Qt::KeepAspectRatio));
    deletelabel = new clickablelabel("-");
    deletelabel->setPixmap(QPixmap(u8":/img/删除.png").scaled(25,25,Qt::KeepAspectRatio));

    toollayout = new QHBoxLayout();
    toollayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    toollayout->addWidget(maxinumlabel);
    toollayout->addWidget(deletelabel);

    tool_space = new QVBoxLayout();
    tool_space->addLayout(toollayout);
    tool_space->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));

    itemlayout = new QHBoxLayout();
    itemlayout->addWidget(name);
    itemlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    itemlayout->addWidget(time);

    mainlayout = new QHBoxLayout();
    mainlayout->addLayout(itemlayout);
    mainlayout->addLayout(tool_space);

    this->setStyleSheet("color:rgb(255,255,255)");
    this->setFrameShape(QFrame::Box);
    this->setFixedHeight(80);
    this->setLayout(mainlayout);
}
