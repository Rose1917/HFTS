#include "little_stratgymanageitem.h"
#include<QFile>
#include<QDir>
#include<QDebug>
#include<QDateTime>
#include<iostream>
#include"common.h"
little_stratgymanageitem::little_stratgymanageitem(QString p)
{
    path = p;
    stratgy = new stratgymanageitem();

    income_expenditure = 0;
    button_delete = new clickablelabel();
    button_delete->setPixmap(QPixmap(u8":/img/删除.png").scaled(25,25,Qt::KeepAspectRatio));
    //button_delete->setStyleSheet("background-color:rgb(255,255,255)");
    button_maxinum = new clickablelabel("+");
    button_maxinum->setPixmap(QPixmap(u8":/img/添加合约.png").scaled(25,25,Qt::KeepAspectRatio));
    //button_maxinum->setStyleSheet("background-color:rgb(255,255,255)");
    label_icon = new QLabel();
    label_icon->setPixmap(QPixmap(u8":/img/策略子项目.png").scaled(40,40,Qt::KeepAspectRatio));
    //label_default->setStyleSheet("background-color:rgb(255,255,255)");
    label_stratgy_name = new QLabel("test");
    //label_stratgy_name->setStyleSheet("background-color:rgb(255,255,255)");
    //label_income_expenditure = new QLabel(QString::number(income_expenditure));
    //label_income_expenditure->setStyleSheet("background-color:rgb(255,255,255)");

    hlayout_main = new QHBoxLayout();
    hlayout_tool = new QHBoxLayout();
    tool_info = new QVBoxLayout();
    hlayout_tool->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    hlayout_tool->addWidget(button_maxinum);
    hlayout_tool->addWidget(button_delete);
    hlayout_icon_info = new QHBoxLayout();
    hlayout_info = new QHBoxLayout();
    hlayout_info->addWidget(label_stratgy_name,0,Qt::AlignVCenter);
    //hlayout_info->addWidget(label_income_expenditure,0,Qt::AlignVCenter);
    hlayout_icon_info->addLayout(hlayout_info);


    tool_info->addLayout(hlayout_tool);
    tool_info->addLayout(hlayout_icon_info);

    hlayout_main->addWidget(label_icon);
    hlayout_main->addLayout(tool_info);

    layout = new QVBoxLayout();

    connect(button_maxinum,SIGNAL(clicked()),this,SLOT(on_maxinum_clicked()));
    connect(stratgy,SIGNAL(signal_submit()),this,SLOT(on_change()));
    connect(button_delete,SIGNAL(clicked()),this,SLOT(on_delete_clicked()));

    n = new nontitle();
    n->setContent(stratgy);

    this->setFrameShape(QFrame::Box);
    this->setFixedHeight(80);
    this->setStyleSheet("color:rgb(255,255,255)");

    this->setLayout(layout);
}

void little_stratgymanageitem::on_maxinum_clicked(){
    n->showincenter();
}
void little_stratgymanageitem::on_delete_clicked(){
    emit signal_delete();
}
void little_stratgymanageitem::on_change(){
    stratgymanageitem* s = qobject_cast<stratgymanageitem*>(sender());
    QString basepath = QDir::currentPath();
    QString dirpath = basepath+"/stratgies/";
    //log_error("little_stratgymanageitem::on_change()");
    //std::cout<<dirpath.toStdString().data()<<std::endl;
    QDir dir;
    if(!dir.exists(dirpath)){
        dir.mkdir(dirpath);
    }
    QFile file(path);

    file.open(QIODevice::WriteOnly);

    QDataStream ds(&file);

    r = s->get_r().toDouble();
    q = s->get_q().toDouble();
    futures_commission = s->get_futures_commission().toDouble();
    futures_cost = s->get_futures_cost().toDouble();
    stock_commission = s->get_stock_commission().toDouble();
    stock_cost = s->get_stock_cost().toDouble();
    stamp_duty = s->get_stamp_duty().toDouble();
    stock_impact_cost = s->get_stock_impact_cost().toDouble();
    stock_index_error = s->get_stock_index_error().toDouble();
    borrowing_cost = s->get_borrowing_cost().toDouble();
    security = s->get_security().toDouble();
    name = s->get_title();

    ds.writeRawData("htfs",4);

    ds<<name;
    label_stratgy_name->setText(name);
    ds<<r;
    ds<<q;
    ds<<futures_commission;
    ds<<futures_cost;
    ds<<stock_commission;
    ds<<stock_cost;
    ds<<stamp_duty;
    ds<<stock_impact_cost;
    ds<<stock_index_error;
    ds<<borrowing_cost;
    ds<<security;

    file.close();
    n->close();
    emit signal_stratgy_changed();
}
void little_stratgymanageitem::getvalues(QString *_n, double *_r, double *_q, double *_futures_commission, double *_futures_cost, double *_stock_commission, double *_stock_cost, double *_stamp_duty, double *_stock_impact_cost, double *_stock_index_error, double *_borrowing_cost,double *_security){
    *_n = name;
    *_r = r;
    *_q = q;
    *_futures_commission = futures_commission;
    *_futures_cost = futures_cost;
    *_stock_commission = stock_commission;
    *_stock_cost = stock_cost;
    *_stamp_duty = stamp_duty;
    *_stock_impact_cost = stock_impact_cost;
    *_stock_index_error = stock_index_error;
    *_borrowing_cost = borrowing_cost;
    *_security = security;
}

void little_stratgymanageitem::setvalues(QString _n, double _r, double _q, double _futures_commission, double _futures_cost, double _stock_commission, double _stock_cost, double _stamp_duty, double _stock_impact_cost, double _stock_index_error, double _borrowing_cost,double _security){
    name = _n;
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

    label_stratgy_name->setText(name);
    stratgy->setvalues(name,
                       r,
                       q,
                       futures_commission,
                       futures_cost,
                       stock_commission,
                       stock_cost,
                       stamp_duty,
                       stock_impact_cost,
                       stock_index_error,
                       borrowing_cost,
                       security);
    layout->addLayout(hlayout_main);
}
QString little_stratgymanageitem::getpath(){
    return path;
}
QString little_stratgymanageitem::getname(){
    return name;
}
