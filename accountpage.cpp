#include "accountpage.h"
#include "include/config.h"
extern econf_ptr econf;
accountpage::accountpage()
{
    market_net = 0;
    trading_net = 0;
    icon = new QLabel();
    icon->setStyleSheet("max-width:150px;max-height:150px;min-height:150px;min-width:150px;border-image:url(':/img/akkarin.png');border-radius:75");
    name = new QLabel(u8"用户名:"+QString::fromStdString(econf->get_investor_id()));
    webconf = new clickablelabel(u8"网络配置");
    passwdchange = new clickablelabel(u8"<a href='http://simnow.com.cn/static/resetPWDPage.action' style='text-decoration:none;color:#ffffff'>忘记密码<\a>");
    passwdchange->setOpenExternalLinks(true);

    sponsorus = new clickablelabel(u8"资助我们");
    money = new QLabel(u8"余额16900000");
    ctpversion = new QLabel(QString::fromStdString(econf->get_ctp_version()));
    ctpversion->setStyleSheet("color:rgb(175,175,175)");

    tradingday = new QLabel(QString::fromStdString(econf->get_trading_day()));
    tradingday->setStyleSheet("color:rgb(175,175,175)");

    mainlayout = new QVBoxLayout();


    mainlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    mainlayout->addWidget(icon,0,Qt::AlignCenter);
    mainlayout->addSpacing(20);
    mainlayout->addWidget(name,0,Qt::AlignCenter);
    mainlayout->addWidget(money,0,Qt::AlignCenter);
    mainlayout->addSpacing(20);
    mainlayout->addWidget(webconf,0,Qt::AlignCenter);
    mainlayout->addWidget(passwdchange,0,Qt::AlignCenter);
    mainlayout->addWidget(sponsorus,0,Qt::AlignCenter);
    mainlayout->addSpacing(40);
    mainlayout->addWidget(ctpversion,0,Qt::AlignCenter);
    mainlayout->addWidget(tradingday,0,Qt::AlignCenter);
    mainlayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));


    this->setStyleSheet(u8"color:rgb(255,255,255);font:20px '黑体'");
    this->setLayout(mainlayout);

    _webconfig = new webconfig();
    webconfigtitle = new nontitle();
    webconfigtitle->setContent(_webconfig);

    connect(webconf,SIGNAL(clicked()),this,SLOT(on_webconf_clicked()));
    connect(sponsorus,SIGNAL(clicked()),this,SLOT(on_sponsorus_clicked()));
    connect(_webconfig,SIGNAL(signal_submit()),this,SLOT(on_webconf_submit()));

}
void accountpage::on_webconf_clicked(){
    webconfigtitle->showincenter();
}
void accountpage::on_webconf_submit(){
    int mem_m = market_net;
    int mem_t = trading_net;
    _webconfig->getconfig(&market_net,&trading_net);
    if(mem_m!=market_net||mem_t!=trading_net){
        emit signal_webconf_changeed();
    }
    webconfigtitle->close();
}
void accountpage::on_passwdchange_clicked(){
    nontitle* n = new nontitle();
    n->setContent(new passwdchangepage());
    n->showincenter();
}
void accountpage::on_sponsorus_clicked(){
    nontitle* n = new nontitle();
    n->setContent(new sponsorpage());
    n->showincenter();
}
void accountpage::getnetconf(int *m, int *t){
    *m = market_net;
    *t = trading_net;
}
