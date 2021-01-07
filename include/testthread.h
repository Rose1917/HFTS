#ifndef TESTTHREAD_H
#define TESTTHREAD_H


#include <QObject>
#include <QThread>
#include "mainwindow.h"
#include "linechartblockview.h"

class TestThread:public QThread
{
    Q_OBJECT
private:
    LineChartBlockView* w;
    int type;
public:
    TestThread(LineChartBlockView* w,int type);
public slots:
    void run() override;
};


#endif // TESTTHREAD_H
