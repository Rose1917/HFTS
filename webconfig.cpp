#include "webconfig.h"

webconfig::webconfig()
{
    labelmarketconfig = new QLabel(u8"市场链接");
    labeltradingconfig = new QLabel(u8"交易链接");
    marketconfig = new QComboBox();
    marketconfig->setStyleSheet("border-style:solid;border-width:2;border-color:rgb(255,255,255);background-color:rgb(44,44,44)");
    marketconfig->addItem("link1");
    marketconfig->addItem("link2");
    marketconfig->addItem("link3");
    marketconfig->addItem("link4");
    marketconfig->addItem("link5");
    //marketconfig->setFont(QFont(u8"黑体",14));
    tradingconfig = new QComboBox();
    tradingconfig->setStyleSheet("border-style:solid;border-width:2;border-color:rgb(255,255,255);background-color:rgb(44,44,44)");
    tradingconfig->addItem("link1");
    tradingconfig->addItem("link2");
    tradingconfig->addItem("link3");
    tradingconfig->addItem("link4");
    tradingconfig->addItem("link5");
    //tradingconfig->setFont(QFont(u8"黑体",14));
    submit = new QPushButton(u8"确定");
    submit->setMinimumHeight(30);
    submit->setMinimumWidth(120);
    submit->setMaximumWidth(160);
    settinglayout = new QHBoxLayout();
    settinglayout->addSpacerItem(new QSpacerItem(10,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    settinglayout->addWidget(labelmarketconfig);
    settinglayout->addWidget(marketconfig);
    settinglayout->addSpacerItem(new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    settinglayout->addWidget(labeltradingconfig);
    settinglayout->addWidget(tradingconfig);
    settinglayout->addSpacerItem(new QSpacerItem(10,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    mainlayout = new QVBoxLayout();
    mainlayout->addLayout(settinglayout);
    mainlayout->addSpacerItem(new QSpacerItem(0,20,QSizePolicy::Expanding,QSizePolicy::Expanding));
    mainlayout->addWidget(submit,0,Qt::AlignHCenter);

    marketconfig_value = marketconfig->currentIndex();
    tradingconfig_value = tradingconfig->currentIndex();

    submit->setStyleSheet("background-color: rgb(255, 200, 64);border-radius: 5px;color: rgb(47,53,46)");

    this->setStyleSheet(u8"color:rgb(255,255,255);font:14pt '黑体'");

    this->setLayout(mainlayout);

    connect(submit,SIGNAL(clicked()),this,SLOT(on_submit_clicked()));
}
void webconfig::on_submit_clicked(){
    marketconfig_value = marketconfig->currentIndex();
    tradingconfig_value = tradingconfig->currentIndex();
    emit signal_submit();
}
void webconfig::getconfig(int *n, int *t){
    *n = marketconfig_value;
    *t = tradingconfig_value;
}
