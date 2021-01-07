#ifndef STRATGYMANEGEITEM_H
#define STRATGYMANEGEITEM_H

#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include"editlabel.h"

class stratgymanageitem:public QWidget
{
    Q_OBJECT
public:
    stratgymanageitem();
    void setvalues(
              QString n,
              double _r,
              double _q,
              double _futures_commission,
              double _futures_cost,
              double _stock_commission,
              double _stock_cost,
              double _stamp_duty,
              double _stock_impact_cost,
              double _stock_index_error,
              double _borrowing_cost);
    QString get_title();
    QString get_r();
    QString get_q();
    QString get_futures_commission();
    QString get_futures_cost();
    QString get_stock_commission();
    QString get_stock_cost();
    QString get_stamp_duty();
    QString get_stock_impact_cost();
    QString get_stock_index_error();
    QString get_borrowing_cost();
private:
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
    QString name;

    editlabel* title;

    QLabel* split_line_1;
    QLabel* split_line_2;

    QLabel* label_r;
    QLabel* label_q;
    QLabel* label_futures_commission;
    QLabel* label_futures_cost;
    QLabel* label_stock_commission;
    QLabel* label_stock_cost;
    QLabel* label_stamp_duty;
    QLabel* label_stock_impact_cost;
    QLabel* label_stock_index_error;
    QLabel* label_borrowing_cost;

    QLineEdit* lineedit_r;
    QLineEdit* lineedit_q;
    QLineEdit* lineedit_futures_commission;
    QLineEdit* lineedit_futures_cost;
    QLineEdit* lineedit_stock_commission;
    QLineEdit* lineedit_stock_cost;
    QLineEdit* lineedit_stamp_duty;
    QLineEdit* lineedit_stock_impact_cost;
    QLineEdit* lineedit_stock_index_error;
    QLineEdit* lineedit_borrowing_cost;

    QHBoxLayout* hlayout_r;
    QHBoxLayout* hlayout_q;
    QHBoxLayout* hlayout_futures_commission;
    QHBoxLayout* hlayout_futures_cost;
    QHBoxLayout* hlayout_stock_commission;
    QHBoxLayout* hlayout_stock_cost;
    QHBoxLayout* hlayout_stamp_duty;
    QHBoxLayout* hlayout_stock_impact_cost;
    QHBoxLayout* hlayout_stock_index_error;
    QHBoxLayout* hlayout_borrowing_cost;

    QPushButton* submit;
    QVBoxLayout* vlayout;
private slots:
    void on_submit_clicked();
signals:
    void signal_submit();
};

#endif // STRATGYMANEGEITEM_H
