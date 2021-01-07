#include "datapage.h"
#include"testthread.h"
std::unordered_map<std::string,datapageitem*> *datapage::item_set=new std::unordered_map<std::string,datapageitem*>();
datapage::datapage()
{
    mainlayout = new QVBoxLayout();
    blocklayout = new QHBoxLayout();
    itemlayout = new QVBoxLayout();
    defaultitem = new datapageitemdefault();
    inputwidget = new datapageiteminput();
    inputwidgettitle = new nontitle();
    inputwidgettitle->setContent(inputwidget);

    l1 = new LineChartBlockView(QString(u8"上证50"),20,5000,20);
    l1->add_lineseries("line1",QPen(QBrush(Qt::red),1,Qt::SolidLine),QColor(255,255,255));
    l2 = new LineChartBlockView(QString(u8"中证500"),20,7000,20);
    l2->add_lineseries("line1",QPen(QBrush(Qt::green),1,Qt::SolidLine),QColor(255,255,255));//加一条红色的线
    //l2->add_lineseries("line1",QPen(QBrush(Qt::yellow),2,Qt::SolidLine),QColor(255,255,255));//加一条黄色的线
    //l2->add_lineseries("line1",QPen(QBrush(Qt::green),2,Qt::SolidLine),QColor(255,255,255));//加一条绿色的线
    l3 = new LineChartBlockView(QString(u8"沪深300"),20,7000,20);
    l3->add_lineseries("line1",QPen(QBrush(Qt::yellow),1,Qt::SolidLine),QColor(255,255,255));
    l1->setMaximumHeight(300);
    l2->setMaximumHeight(300);
    l3->setMaximumHeight(300);

    /*TO-DO*/
    /*
     * 这里对数据进行修改
     * 对应接口函数为 LineChartBlockView::update_line(qread x,qread y,int index)
     * x,y分别表示横纵坐标,index为线的标号,根据添加的顺序确定,如果index超过线的数量或小于0操作无效
     */
    //TestThread* t1 = new TestThread(l2,0);
    //t1->start();

    /*-----*/

    QScrollArea *itempage = new QScrollArea();

    items = new QWidget();
    items_ = new QVBoxLayout();

    scrollspacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);

    items_->addWidget(defaultitem);
    items_->addSpacerItem(scrollspacer);
    items->setLayout(items_);

    itempage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    itempage->setWidget(items);
    itempage->setWidgetResizable(true);
    itempage->setFixedHeight(400);

    itemlayout->addWidget(itempage);

    blocklayout->addWidget(l1);
    blocklayout->addWidget(l2);
    blocklayout->addWidget(l3);

    mainlayout->addLayout(blocklayout);
    mainlayout->addLayout(itemlayout);

    this->setLayout(mainlayout);
    connect(defaultitem->getlabel(),SIGNAL(clicked()),this,SLOT(on_add_item()));
    connect(inputwidget,SIGNAL(on_submit()),this,SLOT(on_item_submit()));
}
void datapage::on_add_item(){
    inputwidget->setname("default");
    inputwidgettitle->show();
    inputwidgettitle->move((deskdop->width()-inputwidgettitle->width())/2, (deskdop->height()-inputwidgettitle->height())/2);
}

void datapage::adddataitem(){
    items_->removeWidget(defaultitem);
    items_->removeItem(scrollspacer);
    datapageitem* item = new datapageitem();
    item->setname("test");
    item->setprice(0.0);
    item->setrise_fall(0.0);
    connect(item,SIGNAL(deletelabel_clicked()),this,SLOT(on_deletelabel_clicked()));
    connect(item,SIGNAL(addtostratgy_clicked()),this,SLOT(on_addtostratgy_clicked()));
    items_->addWidget(item);
    items_->addWidget(defaultitem);
    items_->addSpacerItem(scrollspacer);
}
void datapage::on_item_submit(){
    items_->removeWidget(defaultitem);
    items_->removeItem(scrollspacer);
    datapageitem* newdatapageitem= new datapageitem();
    newdatapageitem->setname(inputwidget->getname());
    //insert the item name and pointer to the set
    log_error("on item submit testing:");
    if(this->item_set==nullptr)log_error("item_set null ptr");
    else (*(this->item_set))[inputwidget->getname().toStdString()]= newdatapageitem;

    //to send the information into the model
    char* temp_name=new char[10]();
    strcpy(temp_name,inputwidget->getname().toUtf8().constData());
    instrument_handler::insert_instru(temp_name);

    connect(newdatapageitem,SIGNAL(deletelabel_clicked()),this,SLOT(on_deletelabel_clicked()));
    connect(newdatapageitem,SIGNAL(addtostratgy_clicked()),this,SLOT(on_addtostratgy_clicked()));

    items_->addWidget(newdatapageitem);
    items_->addWidget(defaultitem);
    items_->addSpacerItem(scrollspacer);
    inputwidgettitle->close();


}

void datapage::on_addtostratgy_clicked(){
    /*TO-DO*/
    datapageitem* s = qobject_cast<datapageitem*>(sender());



}
void datapage::on_deletelabel_clicked(){
    datapageitem* s = qobject_cast<datapageitem*>(sender());
    char* pt=new char[7]();
    strcpy(pt,s->getname().toStdString().data());
    instrument_handler::remove_instru(pt);
    s->close();
}
