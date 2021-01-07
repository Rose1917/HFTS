#include "sponsorpage.h"

sponsorpage::sponsorpage()
{
    icon = new QLabel();
    mainlayout = new QVBoxLayout();
    icon->setPixmap(QPixmap(u8":/img/资助我们.png").scaled(600,600,Qt::KeepAspectRatio));

    mainlayout->addWidget(icon);

    this->setLayout(mainlayout);
}
