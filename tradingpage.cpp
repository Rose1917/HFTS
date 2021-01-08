#include "tradingpage.h"
tradingpage::tradingpage()
{
    stratgyselector = new QComboBox();
    stratgyselector->setMinimumSize(300,40);
    stratgyselector->setStyleSheet("border-style:solid;border-width:2;border-color:rgb(255,255,255)");
    start = new clickablelabel("start");
    start->setPixmap(QPixmap(u8":/img/开始交易.png").scaled(40,40,Qt::KeepAspectRatio));
    stop = new clickablelabel("stop");
    stop->setPixmap(QPixmap(u8":/img/停止交易.png").scaled(40,40,Qt::KeepAspectRatio));
    clear = new clickablelabel("clear");
    clear->setPixmap(QPixmap(u8":/img/删除.png").scaled(40,40,Qt::KeepAspectRatio));

    mainlayout = new QVBoxLayout();
    toollayout = new QHBoxLayout();
    recordlayout = new QHBoxLayout();

    recordtext = new QPlainTextEdit();
    recordtext->setFont(QFont(u8"黑体",10));
    recordtext->setReadOnly(true);
    recordtext->setStyleSheet("border-style:solid;border-width:2;border-color:rgb(255,255,255)");
    //recordtext->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    stratgyselector->setFont(QFont(u8"黑体",14));

    toollayout->addWidget(stratgyselector);
    toollayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    toollayout->addWidget(start);
    toollayout->addWidget(stop);
    toollayout->addWidget(clear);

    recordlayout->addWidget(recordtext);

    mainlayout->addLayout(toollayout);
    mainlayout->addLayout(recordlayout);

    this->setStyleSheet("color:rgb(255,255,255)");
    this->setLayout(mainlayout);

    connect(start,SIGNAL(clicked()),this,SLOT(on_start()));
    connect(stop,SIGNAL(clicked()),this,SLOT(on_stop()));
    connect(clear,SIGNAL(clicked()),this,SLOT(on_clear()));
    //connect(recordtext,SIGNAL(cursorPositionChanged()),this,SLOT(autoscroll()));
}
QComboBox* tradingpage::get_stratgyselector(){
    return stratgyselector;
}
QPlainTextEdit* tradingpage::get_recordtext(){
    return recordtext;
}
void tradingpage::on_start(){
    emit signal_start();
}
void tradingpage::on_stop(){
    emit signal_stop();
}
void tradingpage::on_clear(){
    recordtext->clear();
}
void tradingpage::appendText(QString text){
    recordtext->appendPlainText(text);
}
