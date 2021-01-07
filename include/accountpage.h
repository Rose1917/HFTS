#ifndef ACCOUNTPAGE_H
#define ACCOUNTPAGE_H

#include<QLabel>
#include"clickablelabel.h"
#include<QWidget>
#include<QBoxLayout>
#include"webconfig.h"
#include"nontitle.h"
#include"sponsorpage.h"
#include"passwdchangepage.h"

class accountpage : public QWidget
{
    Q_OBJECT
public:
    accountpage();
    void getnetconf(int* market_net,int* trading_net);
private:
    int market_net;
    int trading_net;

    QLabel* icon;
    QLabel* name;
    clickablelabel* webconf;
    clickablelabel* passwdchange;
    clickablelabel* sponsorus;
    QLabel* money;
    QLabel* ctpversion;
    QLabel* tradingday;

    QVBoxLayout* mainlayout;

    webconfig* _webconfig;
    nontitle* webconfigtitle;


private slots:
    void on_webconf_clicked();
    void on_webconf_submit();
    void on_passwdchange_clicked();
    void on_sponsorus_clicked();

signals:
    void signal_webconf_changeed();
};

#endif // ACCOUNTPAGE_H
