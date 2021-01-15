#include "stratgymanageitem.h"
#include<QFile>
#include<QDataStream>
#include<QDebug>
#include<QDir>
#include<QDateTime>

stratgymanageitem::stratgymanageitem()
{
    r = 0;
    q = 0;
    futures_commission = 0;
    futures_cost = 0;
    stock_commission = 0;
    stock_cost = 0;
    stamp_duty = 0;
    stock_impact_cost = 0;
    stock_index_error = 0;
    borrowing_cost = 0;
    security = 0;

    title = new editlabel();

    split_line_1 = new QLabel();
    split_line_1->setMaximumHeight(1);
    split_line_1->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255);"));

    split_line_2 = new QLabel();
    split_line_2->setMaximumHeight(1);
    split_line_2->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255);"));

    label_r = new QLabel(u8"年利率");
    label_q = new QLabel(u8"年红利");
    label_futures_commission = new QLabel(u8"期货双边手续费");
    label_futures_cost = new QLabel(u8"期货买卖冲击成本");
    label_stock_commission = new QLabel(u8"股票买卖双边手续费");
    label_stock_cost = new QLabel(u8"股票买卖冲击成本");
    label_stamp_duty = new QLabel(u8"股票交易印花税");
    label_stock_impact_cost = new QLabel(u8"股票买卖冲击成本");
    label_stock_index_error = new QLabel(u8"股票指数跟踪误差");
    label_borrowing_cost = new QLabel(u8"借贷利差成本");
    label_security = new QLabel(u8"安全系数");

    lineedit_r = new QLineEdit("0.0");
    lineedit_q = new QLineEdit("0.0");
    lineedit_futures_commission = new QLineEdit("0.0");
    lineedit_futures_cost = new QLineEdit("0.0");
    lineedit_stock_commission = new QLineEdit("0.0");
    lineedit_stock_cost = new QLineEdit("0.0");
    lineedit_stamp_duty = new QLineEdit("0.0");
    lineedit_stock_impact_cost = new QLineEdit("0.0");
    lineedit_stock_index_error = new QLineEdit("0.0");
    lineedit_borrowing_cost = new QLineEdit("0.0");
    lineedit_security = new QLineEdit("0.0");

    label_r->setMinimumWidth(180);
    label_q->setMinimumWidth(180);
    label_futures_commission->setMinimumWidth(180);
    label_futures_cost->setMinimumWidth(180);
    label_stock_commission->setMinimumWidth(180);
    label_stock_cost->setMinimumWidth(180);
    label_stamp_duty->setMinimumWidth(180);
    label_stock_impact_cost->setMinimumWidth(180);
    label_stock_index_error->setMinimumWidth(180);
    label_borrowing_cost->setMinimumWidth(180);
    label_security->setMinimumWidth(180);

    vlayout = new QVBoxLayout();
    hlayout_r = new QHBoxLayout();
    hlayout_r->addWidget(label_r);
    hlayout_r->addWidget(lineedit_r);


    hlayout_q = new QHBoxLayout();
    hlayout_q->addWidget(label_q);
    hlayout_q->addWidget(lineedit_q);

    hlayout_futures_commission = new QHBoxLayout();
    hlayout_futures_commission->addWidget(label_futures_commission);
    hlayout_futures_commission->addWidget(lineedit_futures_commission);

    hlayout_futures_cost = new QHBoxLayout();
    hlayout_futures_cost->addWidget(label_futures_cost);
    hlayout_futures_cost->addWidget(lineedit_futures_cost);

    hlayout_stock_commission = new QHBoxLayout();
    hlayout_stock_commission->addWidget(label_stock_commission);
    hlayout_stock_commission->addWidget(lineedit_stock_commission);

    hlayout_stock_cost = new QHBoxLayout();
    hlayout_stock_cost->addWidget(label_stock_cost);
    hlayout_stock_cost->addWidget(lineedit_stock_cost);

    hlayout_stamp_duty = new QHBoxLayout();
    hlayout_stamp_duty->addWidget(label_stamp_duty);
    hlayout_stamp_duty->addWidget(lineedit_stamp_duty);

    hlayout_stock_impact_cost = new QHBoxLayout();
    hlayout_stock_impact_cost->addWidget(label_stock_impact_cost);
    hlayout_stock_impact_cost->addWidget(lineedit_stock_impact_cost);

    hlayout_stock_index_error = new QHBoxLayout();
    hlayout_stock_index_error->addWidget(label_stock_index_error);
    hlayout_stock_index_error->addWidget(lineedit_stock_index_error);

    hlayout_borrowing_cost = new QHBoxLayout();
    hlayout_borrowing_cost->addWidget(label_borrowing_cost);
    hlayout_borrowing_cost->addWidget(lineedit_borrowing_cost);

    hlayout_security = new QHBoxLayout();
    hlayout_security->addWidget(label_security);
    hlayout_security->addWidget(lineedit_security);

    vlayout->addWidget(title);
    vlayout->addWidget(split_line_1);
    vlayout->addLayout(hlayout_r);
    vlayout->addLayout(hlayout_q);
    vlayout->addLayout(hlayout_futures_commission);
    vlayout->addLayout(hlayout_futures_cost);
    vlayout->addLayout(hlayout_stock_commission);
    vlayout->addLayout(hlayout_stock_cost);
    vlayout->addLayout(hlayout_stamp_duty);
    vlayout->addLayout(hlayout_stock_impact_cost);
    vlayout->addLayout(hlayout_stock_index_error);
    vlayout->addLayout(hlayout_borrowing_cost);
    vlayout->addLayout(hlayout_security);
    vlayout->addWidget(split_line_2);

    submit = new QPushButton(u8"确定");
    submit->setStyleSheet("background-color: rgb(255, 200, 64);border-radius: 5px;color: rgb(47,53,46);font: 12pt '黑体';");
    submit->setMinimumHeight(30);
    submit->setMinimumWidth(120);
    submit->setMaximumWidth(160);


    vlayout->addWidget(submit,0,Qt::AlignCenter);

    this->setLayout(vlayout);

    setFixedSize(400, 460);

    this->setStyleSheet(QStringLiteral("background-color:rgb(44,44,44);color:rgb(255,255,255);font: 10pt '黑体';"));


    connect(submit,SIGNAL(clicked()),this,SLOT(on_submit_clicked()));
}

void stratgymanageitem::on_submit_clicked(){
    emit signal_submit();
    qDebug()<<"submit";
}
void stratgymanageitem::setvalues(QString n,double _r, double _q, double _futures_commission, double _futures_cost, double _stock_commission, double _stock_cost, double _stamp_duty, double _stock_impact_cost, double _stock_index_error, double _borrowing_cost,double _security){
    name = n;
    r = _r;
    q = _q;
    futures_commission = _futures_commission;
    futures_cost = _futures_cost;
    stock_commission = _stock_commission;
    stock_cost = _stock_cost;
    stamp_duty = _stamp_duty;
    stock_impact_cost = _stock_impact_cost;
    stock_index_error = _stock_index_error;
    borrowing_cost = _borrowing_cost;
    security = _security;

    title->setText(name);
    lineedit_r->setText(QString::number(r));
    lineedit_q->setText(QString::number(q));
    lineedit_futures_commission->setText(QString::number(futures_commission));
    lineedit_futures_cost->setText(QString::number(futures_cost));
    lineedit_stock_commission->setText(QString::number(stock_commission));
    lineedit_stock_cost->setText(QString::number(stock_cost));
    lineedit_stamp_duty->setText(QString::number(stamp_duty));
    lineedit_stock_impact_cost->setText(QString::number(stock_impact_cost));
    lineedit_stock_index_error->setText(QString::number(stock_index_error));
    lineedit_borrowing_cost->setText(QString::number(borrowing_cost));
    lineedit_security->setText(QString::number(security));
}

QString stratgymanageitem::get_r(){
    return lineedit_r->text();
}
QString stratgymanageitem::get_q(){
    return lineedit_q->text();
}
QString stratgymanageitem::get_futures_commission(){
    return lineedit_futures_commission->text();
}
QString stratgymanageitem::get_futures_cost(){
    return lineedit_futures_cost->text();
}
QString stratgymanageitem::get_stock_commission(){
    return lineedit_stock_commission->text();
}
QString stratgymanageitem::get_stock_cost(){
    return lineedit_stock_cost->text();
}
QString stratgymanageitem::get_stamp_duty(){
    return lineedit_stamp_duty->text();
}
QString stratgymanageitem::get_stock_impact_cost(){
    return lineedit_stock_impact_cost->text();
}
QString stratgymanageitem::get_stock_index_error(){
    return lineedit_stock_index_error->text();
}
QString stratgymanageitem::get_borrowing_cost(){
    return lineedit_borrowing_cost->text();
}
QString stratgymanageitem::get_title(){
    return title->text();
}
QString stratgymanageitem::get_security(){
    return lineedit_security->text();
}
