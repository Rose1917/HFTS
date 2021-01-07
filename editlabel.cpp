#include "editlabel.h"

editlabel::editlabel()
{
    this->setText(u8"双击修改策略名");
    this->setReadOnly(true);
    this->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->setStyleSheet("QLineEdit{border-width:0;border-style:outset;color:rgb(255,255,255)}");
}

void editlabel::mouseDoubleClickEvent(QMouseEvent *event){
    this->setReadOnly(false);
}

void editlabel::focusOutEvent(QFocusEvent *){
    this->setReadOnly(true);
}
