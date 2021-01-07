#include "datapageitem.h"
#include "subscribtion.h"


datapageitem::datapageitem()
{
    mainlayout = new QHBoxLayout();
    toollayout = new QHBoxLayout();
    itemlayout = new QHBoxLayout();
    tool_rf = new QVBoxLayout();
    name = new QLabel("testname");
    name->setStyleSheet(u8"font: 16pt '黑体';");
    price = new QLabel("0.0");
    price->setStyleSheet(u8"font: 12pt '黑体';color: red");
    rise_fall = new QLabel("0.0");
    deletelabel = new clickablelabel();
    deletelabel->setPixmap(QPixmap(u8":/img/删除.png").scaled(25,25,Qt::KeepAspectRatio));
    addtostratgy = new clickablelabel();
    addtostratgy->setPixmap(QPixmap(u8":/img/添加监控.png").scaled(25,25,Qt::KeepAspectRatio));
    showmore = new clickablelabel();
    showmore->setPixmap(QPixmap(u8":/img/添加合约.png").scaled(25,25,Qt::KeepAspectRatio));
    removestratgy = new clickablelabel();
    removestratgy->setPixmap(QPixmap(u8":/img/移除监控.png").scaled(25,25,Qt::KeepAspectRatio));

    mark = new QLabel("");
    mark->setStyleSheet(u8"font: 10pt '黑体';color:green");

    //toollayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    toollayout->addWidget(showmore);
    toollayout->addWidget(addtostratgy);
    toollayout->addWidget(removestratgy);
    toollayout->addWidget(deletelabel);

    itemlayout->addWidget(name,0,Qt::AlignCenter);
    itemlayout->addWidget(mark,0,Qt::AlignCenter);
    itemlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
    itemlayout->addWidget(price,0,Qt::AlignCenter);
    itemlayout->addSpacerItem(new QSpacerItem(20,0));


    tool_rf->addLayout(toollayout);
    tool_rf->addWidget(rise_fall,0,Qt::AlignBottom|Qt::AlignHCenter);

    mainlayout->addLayout(itemlayout);
    mainlayout->addLayout(tool_rf);

    this->setLayout(mainlayout);
    this->setStyleSheet("color:rgb(255,255,255)");
    this->setFrameShape(QFrame::Box);
    this->setFixedHeight(80);

    connect(deletelabel,SIGNAL(clicked()),this,SLOT(on_deletelabel_clicked()));
    connect(addtostratgy,SIGNAL(clicked()),this,SLOT(on_addtostratgy_clicked()));
    connect(showmore,SIGNAL(clicked()),this,SLOT(on_showmore_clicked()));
    connect(removestratgy,SIGNAL(clicked()),this,SLOT(on_removestratgy_clicked()));

}
void datapageitem::setname(QString n){
    name->setText(n);
}
void datapageitem::setprice(double p){
    price->setText(QString::number(p));
}
void datapageitem::setrise_fall(double rf){
    rise_fall->setText(QString::number(rf));
}
void datapageitem::on_deletelabel_clicked(){
    emit deletelabel_clicked();
}
void datapageitem::on_showmore_clicked(){
    nontitle* n = new nontitle();
    datapageitemshowmore* showmore = new datapageitemshowmore();

    char* temp_ins=new char[7]();
    strcpy(temp_ins,name->text().toStdString().data());

    instrument_item* it=instrument_handler::get_instrument_by_id(temp_ins);
    for(auto& i:*(it->get_prices())){
       showmore->addRow(QString::fromStdString(std::string(i->time.operator SAString().GetMultiByteChars())),i->value);
    }

    n->setContent(showmore);
    n->showincenter();
}
void datapageitem::on_addtostratgy_clicked(){
    mark->setText(u8"已监控");

    //emit addtostratgy_clicked();

    /*TO-DO*/
}
void datapageitem::on_removestratgy_clicked(){
    mark->setText("");

    /*TO-DO*/

//3650599367aA
}
QString datapageitem::getname(){
    return name->text();
}
