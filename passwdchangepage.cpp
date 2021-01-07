#include "passwdchangepage.h"

passwdchangepage::passwdchangepage()
{
    orig_passwd = new QLabel(u8"原密码");
    orig_passwd->setStyleSheet("color:rgb(255,255,255)");
    new_passwd = new QLabel(u8"新密码");
    new_passwd->setStyleSheet("color:rgb(255,255,255)");
    confirm_passwd = new QLabel(u8"再次输入新密码");
    confirm_passwd->setStyleSheet("color:rgb(255,255,255)");

    edit_orig_passwd = new QLineEdit();
    edit_new_passwd = new QLineEdit();
    edit_confirm_passwd = new QLineEdit();

    edit_orig_passwd->setEchoMode(QLineEdit::Password);
    edit_new_passwd->setEchoMode(QLineEdit::Password);
    edit_confirm_passwd->setEchoMode(QLineEdit::Password);

    submit = new QPushButton(u8"确认");
    submit->setMinimumHeight(30);
    submit->setMinimumWidth(120);
    submit->setMaximumWidth(160);
    submit->setStyleSheet("background-color: rgb(255, 200, 64);border-radius: 5px;color: rgb(47,53,46)");

    inputlayout = new QGridLayout();
    inputlayout->addWidget(orig_passwd,0,0);
    inputlayout->addWidget(edit_orig_passwd,0,1);
    inputlayout->addWidget(new_passwd,1,0);
    inputlayout->addWidget(edit_new_passwd,1,1);
    inputlayout->addWidget(confirm_passwd,2,0);
    inputlayout->addWidget(edit_confirm_passwd,2,1);

    mainlayout = new QVBoxLayout();

    mainlayout->addLayout(inputlayout);
    mainlayout->addSpacing(20);
    mainlayout->addWidget(submit,0,Qt::AlignHCenter);

    this->setStyleSheet(u8"font: 12pt '黑体'");


    this->setLayout(mainlayout);

    connect(submit,SIGNAL(clicked()),this,SLOT(on_submit_clicked()));
}
void passwdchangepage::on_submit_clicked(){
    /*TO-DO*/
}
