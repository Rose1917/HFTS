#ifndef DATAPAGEITEM_H
#define DATAPAGEITEM_H

#include<QFrame>
#include<QBoxLayout>
#include<QLabel>
#include"clickablelabel.h"
#include"datapageitemshowmore.h"
#include"nontitle.h"
class datapageitem : public QFrame
{
    Q_OBJECT
public:
    datapageitem();
    void setname(QString n);
    QString getname();
    void setprice(double p);
    void setrise_fall(double rf);

private:

    /*QVBoxLayout* mainlayout;
    QHBoxLayout* toollayout;
    QHBoxLayout* itemlayout;*/


    QHBoxLayout* mainlayout;
    QHBoxLayout* itemlayout;

    QHBoxLayout* toollayout;
    QVBoxLayout* tool_rf;

    clickablelabel* showmore;
    clickablelabel* deletelabel;
    clickablelabel* addtostratgy;
    clickablelabel* removestratgy;

    QLabel* name;
    QLabel* mark;
    QLabel* price;
    QLabel* rise_fall;
signals:
    void deletelabel_clicked();
    void addtostratgy_clicked();
private slots:
    void on_deletelabel_clicked();
    void on_addtostratgy_clicked();
    void on_showmore_clicked();
    void on_removestratgy_clicked();
};

#endif // DATAPAGEITEM_H
