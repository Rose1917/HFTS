#include "datapageitemshowmore.h"
#include "include/common.h"
datapageitemshowmore::datapageitemshowmore()
{
    tableview = new QTableWidget();
    mainlayout = new QVBoxLayout();

    tableview->setColumnCount(2);
    tableview->setHorizontalHeaderLabels(QStringList()<<u8"合约名"<<u8"价格");
    //tableview->setModel(model);
    //tableview->setEnabled(false);
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //tableview->setMinimumSize(400,400);

    tableview->setStyleSheet("background-color:rgb(44,44,44)");
    tableview->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(44,44,44);}");
    tableview->verticalHeader()->hide();

    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableview->setMinimumSize(400,400);

    mainlayout->addWidget(tableview);

    this->setStyleSheet("color:rgb(255,255,255)");

    this->setLayout(mainlayout);
}
void datapageitemshowmore::addRow(QString name, double price){
    log_error("datapageitemshowmore::addRow");
    std::cout<<"Value:"<<price<<endl;
    int rowcount = tableview->rowCount();
    tableview->insertRow(rowcount);
    tableview->setItem(rowcount,0,new QTableWidgetItem(name));
    tableview->setItem(rowcount,1,new QTableWidgetItem(QString::number(price)));
}
