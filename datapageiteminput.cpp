#include "datapageiteminput.h"

datapageiteminput::datapageiteminput()
{
    label_name = new QLabel(u8"合约号");
    lineedit_name = new QLineEdit(u8"default");
    submit = new QPushButton(u8"确定");
    submit->setStyleSheet("background-color: rgb(255, 200, 64);border-radius: 5px;color: rgb(47,53,46);font: 14pt '黑体';");
    submit->setMinimumHeight(30);
    submit->setMinimumWidth(120);
    submit->setMaximumWidth(160);
    mainlayout = new QVBoxLayout();

    namelayout = new QHBoxLayout();
    namelayout->addWidget(label_name);
    namelayout->addWidget(lineedit_name);

    mainlayout->addLayout(namelayout);
    mainlayout->addWidget(submit,0,Qt::AlignCenter);

    connect(submit,SIGNAL(clicked()),this,SLOT(on_submit_clicked()));

    this->setStyleSheet(QStringLiteral("background-color:rgb(44,44,44);color:rgb(255,255,255);font: 12pt '黑体';"));

    this->setLayout(mainlayout);
}

void datapageiteminput::on_submit_clicked(){
    emit on_submit();
}
QString datapageiteminput::getname(){
    return lineedit_name->text();
}
void datapageiteminput::setname(QString n){
    lineedit_name->setText(n);
}
