#ifndef INITWINDOW_H
#define INITWINDOW_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QComboBox>
#include "linechartblockview.h"
#include "clickablelabel.h"
#include <QDebug>
#include "linechartblockview.h"
#include "testthread.h"
#include "stratgymanageitem.h"
#include "datapage.h"
#include "stratgymanagepage.h"
#include "tradingpage.h"
#include "orderpage.h"
#include "accountpage.h"
class datapage;
class InitWindow : public QWidget
{
    Q_OBJECT
public:
    QHBoxLayout *MainView;
    QVBoxLayout *MenuLayout;
    QLabel *title;
    clickablelabel *data_view;
    clickablelabel *strategy_manage;
    clickablelabel *account_manage;
    clickablelabel *order_manage;
    clickablelabel *trading;
    QSpacerItem *verticalSpacer;
    QLabel *Menu_Page;
    QVBoxLayout *PageLayout;
    QLabel *workspace;
    QStackedWidget *Pages;
    QWidget *data_page;
    QWidget *strategy_page;
    QWidget *account_page;
    QWidget *order_page;
    QWidget *trading_page;
    QLabel *label_10;

    stratgymanagepage* _strategypage;
    datapage* _datapage;
    tradingpage* _tradingpage;
    orderpage* _orderpage;
    accountpage* _accountpage;
    InitWindow();

    int trading_status;

    void addorder_request(QString id,QString time,QString status);
    void setorderstatus_request(QString id,QString status);
    void appendText_request(QString text);
private slots:

    void on_data_view_clicked();

    void on_strategy_manage_clicked();

    void on_account_manage_clicked();

    void on_order_manage_clicked();

    void on_trading_clicked();

    void on_enlarge(LineChartBlockView* view);

    void on_stratgy_changed();

    void on_trading_start();
    void on_trading_stop();

private:
    void init_data_page();
    void init_trading_page();
    void init_strategy_page();
    void init_account_page();
    void init_order_page();
signals:
    void addorder(QString id,QString time,QString status);
    void setorderstatus(QString id,QString status);
    void appendText(QString text);
};

#endif // INITWINDOW_H
