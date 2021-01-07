#ifndef DATAPAGEITEMSHOWMORE_H
#define DATAPAGEITEMSHOWMORE_H

#include<QWidget>
#include<QTableWidget>
#include<QBoxLayout>
#include<QHeaderView>
class datapageitemshowmore : public QWidget
{
    Q_OBJECT
public:
    datapageitemshowmore();
    void addRow(QString name,double price);
private:
    QVBoxLayout* mainlayout;
    QTableWidget* tableview;
};

#endif // DATAPAGEITEMSHOWMORE_H
