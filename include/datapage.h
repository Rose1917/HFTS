#ifndef DATAPAGE_H
#define DATAPAGE_H
#include<QWidget>
#include"common.h"
#include<QBoxLayout>
#include<linechartblockview.h>
#include"datapageitem.h"
#include<QList>
#include"datapageitemdefault.h"
#include"datapageiteminput.h"
#include"nontitle.h"
#include"datapageiteminput.h"
class datapage : public QWidget
{
    Q_OBJECT
public:
    static std::unordered_map<std::string,datapageitem*> *item_set;
    datapage();
    void adddataitem();
    LineChartBlockView* getBlockView(int i){
        switch(i){
            case 1:
                return l1;
            case 2:
                return l2;
            case 3:
                return l3;
            default:
                return nullptr;
        }
    }
private:
    QVBoxLayout* mainlayout;//整体布局
    QHBoxLayout* blocklayout;//存放上方图表
    QVBoxLayout* itemlayout;//存放条目

    LineChartBlockView* l1;
    LineChartBlockView* l2;
    LineChartBlockView* l3;

    datapageitemdefault* defaultitem;

    QSpacerItem* scrollspacer;

    QWidget* items;
    QVBoxLayout* items_;

    QDesktopWidget *deskdop=QApplication::desktop();

    datapageiteminput* inputwidget;
    nontitle* inputwidgettitle;
private slots:
    void on_add_item();
    void on_item_submit();
    void on_addtostratgy_clicked();
    void on_deletelabel_clicked();
};

#endif // DATAPAGE_H
