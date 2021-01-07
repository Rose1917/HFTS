#include "datapageitemdefault.h"

datapageitemdefault::datapageitemdefault()
{
    icon = new clickablelabel();
    icon->setAlignment(Qt::AlignCenter);
    mainlayout = new QVBoxLayout();
    mainlayout->addWidget(icon);
    icon->setPixmap(QPixmap(u8":/img/带圈添加.png").scaled(60,60,Qt::KeepAspectRatio));
    mainlayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainlayout);
    this->setStyleSheet("color:rgb(255,255,255)");
    this->setFrameShape(QFrame::Box);
    this->setFixedHeight(80);
}
clickablelabel* datapageitemdefault::getlabel(){
    return icon;
}
