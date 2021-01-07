#ifndef WEBCONFIG_H
#define WEBCONFIG_H

#include<QWidget>
#include<QComboBox>
#include<QPushButton>
#include<QBoxLayout>
#include<QLabel>
class webconfig : public QWidget
{
    Q_OBJECT
public:
    webconfig();
    void getconfig(int* market_net,int* trading_net);
private:
    int marketconfig_value;
    int tradingconfig_value;

    QLabel* labelmarketconfig;
    QLabel* labeltradingconfig;

    QComboBox* marketconfig;
    QComboBox* tradingconfig;
    QPushButton* submit;

    QHBoxLayout* settinglayout;
    QVBoxLayout* mainlayout;
private slots:
    void on_submit_clicked();
signals:
    void signal_submit();
};

#endif // WEBCONFIG_H
