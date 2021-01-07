#include "testthread.h"
#include "mainwindow.h"

TestThread::TestThread(LineChartBlockView *w,int type){
    this->type = type;
    this->w = w;
    //connect(w,SIGNAL(exit_thread()),this,SLOT(quit_thread()));
}

void TestThread::run(){
    for(int i=1;i<=12800;i++){
        w->data_added();
        qreal x = i;
        qreal y = qrand()%5000;
        if(type==0)w->update_line(x,y,0);
        x = i;
        y = qrand()%5000;
        if(type==0)w->update_line(x,y,1);
        x = i;
        y = qrand()%5000;
        if(type==0)w->update_line(x,y,2);
        msleep(1000);
    }
}
