#include "clickablelabel.h"
#include<QDebug>
clickablelabel::clickablelabel(const QString& text,QWidget* parent):QLabel(parent)
{
    setText(text);
    this->setStyleSheet("clickablelabel:hover{background-color:rgb(120,120,120);}");
}
void clickablelabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug()<<"aaa";
        emit clicked();
    }
    QLabel::mouseReleaseEvent(event);//将该事件传给父类处理
}
