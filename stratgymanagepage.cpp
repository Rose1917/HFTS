#include "stratgymanagepage.h"
#include<QDir>
#include<QFile>
#include<QDebug>
#include<QDateTime>
#include"common.h"
stratgymanagepage::stratgymanagepage()
{
    QScrollArea *itempage = new QScrollArea();

    defaultitem = new stratgymanageitemdefault();
    inputitem = new stratgymanageitem();
    inputitem->setvalues("default",0,0,0,0,0,0,0,0,0,0,0);
    inputiitemtitle = new nontitle();
    inputiitemtitle->setContent(inputitem);

    mainlayout = new QVBoxLayout();
    items = new QWidget();
    itemslayout = new QVBoxLayout();
    scrollspacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);

    QDir dir("./stratgies");
    QStringList nameFilters;
    nameFilters << "*.htfscfg";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);

    QString basepath = QDir::currentPath();
    QString dirpath = basepath+"/stratgies/";

    for(int i=0;i<files.size();i++){
        QString fullpath = dirpath+files.at(i);
        //qDebug()<<fullpath;
        QFile file(fullpath);
        file.open(QIODevice::ReadOnly);
        QDataStream ds(&file);
        char* magic = new char[5];
        magic[4] = '\0';
        ds.readRawData(magic,4);
        //qDebug()<<magic;
        if(strcmp(magic,"htfs")==0){
            little_stratgymanageitem* l = new little_stratgymanageitem(fullpath);
            itemslayout->addWidget(l);
            double r;//年利率
            double q;//年红利
            double futures_commission;//期货双边手续费
            double futures_cost;//期货买卖冲击成本
            double stock_commission;//股票买卖双边手续费
            double stock_cost;//股票买卖冲击成本
            double stamp_duty;//股票交易印花税
            double stock_impact_cost;//股票买卖冲击成本
            double stock_index_error;//股票指数跟踪误差
            double borrowing_cost;//借贷利差成本
            double security;
            QString name;
            ds>>name
              >>r
              >>q
              >>futures_commission
              >>futures_cost
              >>stock_commission
              >>stock_cost
              >>stamp_duty
              >>stock_impact_cost
              >>stock_index_error
              >>borrowing_cost
              >>security;
            l->setvalues(name,r,q,futures_commission,futures_cost,stock_commission,stock_cost,stamp_duty,stock_impact_cost,stock_index_error,borrowing_cost,security);
            connect(l,SIGNAL(signal_delete()),this,SLOT(on_delete_item()));
            connect(l,SIGNAL(signal_stratgy_changed()),this,SLOT(on_item_stratgy_changed()));
            stratgies.append(l);
        }
    }
    itemslayout->addWidget(defaultitem);
    itemslayout->addSpacerItem(scrollspacer);
    items->setLayout(itemslayout);
    itempage->setWidget(items);
    itempage->setWidgetResizable(true);
    itempage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //itempage->setFixedHeight(800);

    mainlayout->addWidget(itempage);

    this->setLayout(mainlayout);

    connect(defaultitem->getlabel(),SIGNAL(clicked()),this,SLOT(on_add_clicked()));
    connect(inputitem,SIGNAL(signal_submit()),this,SLOT(on_item_submit()));
}
void stratgymanagepage::on_add_clicked(){
    inputitem->setvalues("default",0,0,0,0,0,0,0,0,0,0,0);
    inputiitemtitle->showincenter();
}
void stratgymanagepage::on_item_submit(){
    QString basepath = QDir::currentPath();
    QString dirpath = basepath+"/stratgies/";

    QDir dir;
    if(!dir.exists(dirpath)){
        dir.mkdir(dirpath);
    }

    QString data_time = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString path = dirpath+data_time+".htfscfg";

    log_error("little_stratgymanageitem::on_change()");
    std::cout<<dirpath.toStdString().data()<<std::endl;

    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QDataStream ds(&file);

    double r;//年利率
    double q;//年红利
    double futures_commission;//期货双边手续费
    double futures_cost;//期货买卖冲击成本
    double stock_commission;//股票买卖双边手续费
    double stock_cost;//股票买卖冲击成本
    double stamp_duty;//股票交易印花税
    double stock_impact_cost;//股票买卖冲击成本
    double stock_index_error;//股票指数跟踪误差
    double borrowing_cost;//借贷利差成本
    double security;
    QString name;
    name = inputitem->get_title();
    r = inputitem->get_r().toDouble();
    q = inputitem->get_q().toDouble();
    futures_commission = inputitem->get_futures_commission().toDouble();
    futures_cost = inputitem->get_futures_cost().toDouble();
    stock_commission = inputitem->get_stock_commission().toDouble();
    stock_cost = inputitem->get_stock_cost().toDouble();
    stamp_duty = inputitem->get_stamp_duty().toDouble();
    stock_impact_cost = inputitem->get_stock_impact_cost().toDouble();
    stock_index_error = inputitem->get_stock_index_error().toDouble();
    borrowing_cost = inputitem->get_borrowing_cost().toDouble();
    security = inputitem->get_security().toDouble();

    ds.writeRawData("htfs",4);
    ds<<name;
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

    itemslayout->removeItem(scrollspacer);
    itemslayout->removeWidget(defaultitem);

    little_stratgymanageitem* l = new little_stratgymanageitem(path);
    l->setvalues(name,r,q,futures_commission,futures_cost,stock_commission,stock_cost,stamp_duty,stock_impact_cost,stock_index_error,borrowing_cost,security);
    connect(l,SIGNAL(signal_delete()),this,SLOT(on_delete_item()));
    connect(l,SIGNAL(signal_stratgy_changed()),this,SLOT(on_item_stratgy_changed()));
    stratgies.append(l);
    itemslayout->addWidget(l);

    itemslayout->addWidget(defaultitem);
    itemslayout->addSpacerItem(scrollspacer);

    inputiitemtitle->close();



    emit stratgy_changed();
}
void stratgymanagepage::on_delete_item(){
    little_stratgymanageitem* l = qobject_cast<little_stratgymanageitem*>(sender());
    stratgies.removeOne(l);
    QFile::remove(l->getpath());
    l->close();
    emit stratgy_changed();
}
QList<little_stratgymanageitem*> stratgymanagepage::get_stratgies(){
    return stratgies;
}
void stratgymanagepage::on_item_stratgy_changed(){
    emit stratgy_changed();
}
