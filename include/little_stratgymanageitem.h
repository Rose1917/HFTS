#ifndef LITTLE_STRATGYMANAGEITEM_H
#define LITTLE_STRATGYMANAGEITEM_H
#include<QFrame>
#include<QPushButton>
#include<QLabel>
#include<QBoxLayout>
#include<QSpacerItem>
#include<QMouseEvent>
#include"nontitle.h"
#include"clickablelabel.h"
#include"stratgymanageitem.h"
class little_stratgymanageitem : public QFrame
{
    Q_OBJECT
public:
    little_stratgymanageitem(QString path);
    void getvalues(
              QString* _n,
              double* _r,
              double* _q,
              double* _futures_commission,
              double* _futures_cost,
              double* _stock_commission,
              double* _stock_cost,
              double* _stamp_duty,
              double* _stock_impact_cost,
              double* _stock_index_error,
              double* _borrowing_cost,
              double* _security);
    void setvalues(
              QString _n,
              double _r,
              double _q,
              double _futures_commission,
              double _futures_cost,
              double _stock_commission,
              double _stock_cost,
              double _stamp_duty,
              double _stock_impact_cost,
              double _stock_index_error,
              double _borrowing_cost,
              double _security);
    QString getpath();
    QString getname();
private:
    double income_expenditure;

    clickablelabel* button_delete;//删除按钮
    clickablelabel* button_maxinum;//放大按钮
    QLabel* label_icon;
    QLabel* label_stratgy_name;//策略名字
    //QLabel* label_income_expenditure;//收支
    stratgymanageitem* stratgy;
    QHBoxLayout* hlayout_main;
    QHBoxLayout* hlayout_tool;
    QHBoxLayout* hlayout_icon_info;
    QHBoxLayout* hlayout_info;
    QVBoxLayout* layout;
    QVBoxLayout* tool_info;

    nontitle* n;

    QString path;

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
signals:
    void signal_delete();
    void signal_stratgy_changed();
private slots:
    void on_maxinum_clicked();
    void on_delete_clicked();
    void on_change();

};

#endif // LITTLE_STRATGYMANAGEITEM_H
