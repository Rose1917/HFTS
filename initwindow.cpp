#include "initwindow.h"
//#include "include/trade_handler.h"

void InitWindow::init_data_page(){
    _datapage = new datapage();
    ((QGridLayout*)(data_page->layout()))->addWidget(_datapage);
}
void InitWindow::init_order_page(){
    _orderpage = new orderpage();
    ((QGridLayout*)(order_page->layout()))->addWidget(_orderpage);
}
void InitWindow::init_account_page(){
    _accountpage = new accountpage();
    ((QGridLayout*)(account_page->layout()))->addWidget(_accountpage);
}
void InitWindow::init_strategy_page(){
    _strategypage = new stratgymanagepage();
    ((QGridLayout*)(strategy_page->layout()))->addWidget(_strategypage);

    connect(_strategypage,SIGNAL(stratgy_changed()),this,SLOT(on_stratgy_changed()));
}
void InitWindow::init_trading_page(){
    _tradingpage = new tradingpage();
    QComboBox* cb = _tradingpage->get_stratgyselector();
    QList<little_stratgymanageitem*> list = _strategypage->get_stratgies();
    for(int i=0;i<list.size();i++){
        cb->addItem(list.at(i)->getname());
    }
    connect(_tradingpage,SIGNAL(signal_start()),this,SLOT(on_trading_start()));
    connect(_tradingpage,SIGNAL(signal_stop()),this,SLOT(on_trading_stop()));
    ((QGridLayout*)(trading_page->layout()))->addWidget(_tradingpage);
}
void InitWindow::on_enlarge(LineChartBlockView* view){
}
InitWindow::InitWindow()
{
    trading_status = 0;
    //this->setMinimumSize(1600,960);
    this->setStyleSheet(QStringLiteral("background-color:rgb(44,44,44);"));
    MainView = new QHBoxLayout();
    MenuLayout = new QVBoxLayout();
    Menu_Page = new QLabel();//MenuLayout和PageLayout分隔
    PageLayout = new QVBoxLayout();
    Menu_Page->setMinimumWidth(1);
    Menu_Page->setMaximumWidth(1);
    Menu_Page->setStyleSheet(QStringLiteral("background-color:rgb(255,255,255);"));
    MainView->addLayout(MenuLayout);
    MainView->addWidget(Menu_Page);
    MainView->addLayout(PageLayout);
    title = new QLabel();
    title->setMinimumHeight(64);
    title->setMaximumHeight(64);
    title->setFont(QFont("Arial Black",20,QFont::Bold));
    title->setText("HTFS");
    title->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));
    account_manage = new clickablelabel();
    account_manage->setPixmap(QPixmap(u8":/img/我的.png").scaled(100,50,Qt::KeepAspectRatio));
    account_manage->setAlignment(Qt::AlignCenter);
    account_manage->setMinimumHeight(100);
    data_view = new clickablelabel(u8"实时数据");
    data_view->setPixmap(QPixmap(u8":/img/行情.png").scaled(100,50,Qt::KeepAspectRatio));
    data_view->setAlignment(Qt::AlignCenter);
    data_view->setMinimumHeight(100);
    strategy_manage = new clickablelabel(u8"策略配置");
    strategy_manage->setPixmap(QPixmap(u8":/img/策略.png").scaled(100,50,Qt::KeepAspectRatio));
    strategy_manage->setAlignment(Qt::AlignCenter);
    strategy_manage->setMinimumHeight(100);
    order_manage = new clickablelabel(u8"订单管理");
    order_manage->setPixmap(QPixmap(u8":/img/订单.png").scaled(100,50,Qt::KeepAspectRatio));
    order_manage->setAlignment(Qt::AlignCenter);
    order_manage->setMinimumHeight(100);
    trading = new clickablelabel();
    trading->setPixmap(QPixmap(u8":/img/交易.png").scaled(100,50,Qt::KeepAspectRatio));
    trading->setAlignment(Qt::AlignCenter);
    trading->setMinimumHeight(100);



    verticalSpacer = new QSpacerItem(20,40,QSizePolicy::Minimum, QSizePolicy::Expanding);

    MenuLayout->addWidget(title);
    MenuLayout->addWidget(data_view);
    MenuLayout->addWidget(trading);
    MenuLayout->addWidget(strategy_manage);
    MenuLayout->addWidget(order_manage);
    MenuLayout->addWidget(account_manage);
    MenuLayout->addSpacerItem(verticalSpacer);

    Pages = new QStackedWidget();
    //Pages->setStyleSheet(QStringLiteral("background-color: rgb(40,43, 59);"));
    data_page = new QWidget();
    data_page->setLayout(new QGridLayout());
    strategy_page = new QWidget();
    strategy_page->setLayout(new QGridLayout());
    account_page = new QWidget();
    account_page->setLayout(new QGridLayout());
    order_page = new QWidget();
    order_page->setLayout(new QGridLayout());
    trading_page = new QWidget();
    trading_page->setLayout(new QGridLayout());
    Pages->addWidget(data_page);
    Pages->addWidget(trading_page);
    Pages->addWidget(strategy_page);
    Pages->addWidget(account_page);
    Pages->addWidget(order_page);
    label_10 = new QLabel();
    workspace = new QLabel(u8"行情数据");
    workspace->setFont(QFont(u8"黑体",16));
    workspace->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    workspace->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

    PageLayout->addWidget(workspace);
    PageLayout->addWidget(Pages);
    PageLayout->addWidget(label_10);

    Pages->setCurrentIndex(0);

    connect(data_view, SIGNAL(clicked()), this, SLOT(on_data_view_clicked()));
    connect(trading, SIGNAL(clicked()), this, SLOT(on_trading_clicked()));
    connect(strategy_manage, SIGNAL(clicked()), this, SLOT(on_strategy_manage_clicked()));
    connect(account_manage, SIGNAL(clicked()), this, SLOT(on_account_manage_clicked()));
    connect(order_manage, SIGNAL(clicked()), this, SLOT(on_order_manage_clicked()));

    init_data_page();
    init_strategy_page();
    init_trading_page();
    init_order_page();
    init_account_page();

    this->setLayout(MainView);
}


void InitWindow::on_data_view_clicked(){
    Pages->setCurrentIndex(0);
    workspace->setText(u8"行情数据");
}
void InitWindow::on_trading_clicked(){
    Pages->setCurrentIndex(1);
    workspace->setText(u8"交易");
}
void InitWindow::on_strategy_manage_clicked(){
    Pages->setCurrentIndex(2);
    workspace->setText(u8"策略配置");
}

void InitWindow::on_account_manage_clicked(){
    Pages->setCurrentIndex(3);
    workspace->setText(u8"账户管理");
}
void InitWindow::on_order_manage_clicked(){
    Pages->setCurrentIndex(4);
    workspace->setText(u8"订单管理");
}

void InitWindow::on_stratgy_changed(){
    QComboBox* cb = _tradingpage->get_stratgyselector();
    cb->clear();
    QList<little_stratgymanageitem*> list = _strategypage->get_stratgies();
    for(int i=0;i<list.size();i++){
        cb->addItem(list.at(i)->getname());
    }
}
void InitWindow::on_trading_start(){
    if(trading_status==1)return;
    QList<little_stratgymanageitem*> list = _strategypage->get_stratgies();
    QTextEdit* record = _tradingpage->get_recordtext();
    if(list.size()==0){
        record->append(u8"未选择策略，请检查您的策略配置");
    }
    else{
        trading_status = 1;
        QComboBox* cb = _tradingpage->get_stratgyselector();
        little_stratgymanageitem* nowstratgy = list.at(cb->currentIndex());
        record->append(u8"------------------------------------------------");
        record->append(u8"交易开始");
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
        nowstratgy->getvalues(&name,
                              &r,
                              &q,
                              &futures_commission,
                              &futures_cost,
                              &stock_commission,
                              &stock_cost,
                              &stamp_duty,
                              &stock_impact_cost,
                              &stock_index_error,
                              &borrowing_cost);
        record->append(u8"现在正在使用的策略为:"+name);
        record->append(u8"\t年利率\t\t\t"+QString::number(r));
        record->append(u8"\t年红利\t\t\t"+QString::number(q));
        record->append(u8"\t期货双边手续费\t\t"+QString::number(futures_commission));
        record->append(u8"\t期货买卖冲击成本\t\t"+QString::number(futures_cost));
        record->append(u8"\t股票买卖双边手续费\t"+QString::number(stock_commission));
        record->append(u8"\t股票买卖冲击成本\t\t"+QString::number(stock_cost));
        record->append(u8"\t股票交易印花税\t\t"+QString::number(stamp_duty));
        record->append(u8"\t股票买卖冲击成本\t\t"+QString::number(stock_impact_cost));
        record->append(u8"\t股票指数跟踪误差\t\t"+QString::number(stock_index_error));
        record->append(u8"\t借贷利差成本\t\t"+QString::number(borrowing_cost));
        int market_net;
        int trading_net;
        _accountpage->getnetconf(&market_net,&trading_net);
        record->append(u8"网络配置:");
        record->append(u8"\t市场配置:link"+QString::number(market_net+1));
        record->append(u8"\t交易配置:link"+QString::number(trading_net+1));
        /*TO-DO*/
/*
        trade_handler::trade_switch=true;
        trade_handler::strategy->set_name(name.toStdString());
        trade_handler::strategy->setAnnual_interest_rate(r);
        trade_handler::strategy->setAnnual_bonus_rate(q);
        trade_handler::strategy->setFuture_commission(futures_commission);
        trade_handler::strategy->setImpact_cost(futures_cost);
        trade_handler::strategy->setstock_commision_rate(stock_commission);
        trade_handler::strategy->setStock_stamp_duty_rate(stock_cost);
        trade_handler::strategy->setStock_stamp_duty_rate(stamp_duty);
        trade_handler::strategy->setStock_impact_cost(stock_impact_cost);
        trade_handler::strategy->setIndex_track_error_rate(stock_index_error);
        trade_handler::strategy->setCost_borrow_spread(borrowing_cost);
*/
        //trade_handler::strategy-
    }
}
void InitWindow::on_trading_stop(){
    if(trading_status==0)return;
    trading_status = 0;
    _tradingpage->get_recordtext()->append(u8"交易结束");
    _tradingpage->get_recordtext()->append(u8"------------------------------------------------");

    /*TO-DO*/


}
