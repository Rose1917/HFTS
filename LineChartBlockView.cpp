#include "linechartblockview.h"
#include "testthread.h"
#include "debug.h"
#include <iostream>
LineChartBlockView::LineChartBlockView(QString name,int _maxX,int _maxY,int _maxSize)
{
    maxX = _maxX;
    minY = 99999999;
    maxY = 0;
    maxSize = _maxSize;
    datanum = 0;
    data = new QList<double>();
    chart = new QChart();

    lines = new QList<QLineSeries*>();

    chart->setBackgroundBrush(QBrush(QColor(44,44,44)));//设置背景色,主题和背景二选一
    chart->legend()->hide();//legend是否显示，show和hide

    chart->setTitle(name);//设置标题

    chart->setTitleBrush(QBrush(QColor(255,255,255)));//设置标题Brush
    chart->setTitleFont(QFont(u8"黑体",12));//设置标题字体

    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    //this->show();
    this->setMinimumHeight(300);
}
void LineChartBlockView::add_lineseries(QString name,QPen linePen,QColor pointLabelColor){
    QLineSeries *line = new QLineSeries();
    line->setName(name);    //设置线条名称
    //line->setColor(lineColor);     //设置线条颜色
    //line->setPen(QPen(QBrush(Qt::red),2,Qt::SolidLine));
    line->setPen(linePen);
    line->setVisible(true);    //线条是否可视
    line->setPointsVisible(true);//点是否可视
    line->setPointLabelsVisible(false);//点标签是否可视
    line->setPointLabelsColor(pointLabelColor);    //设置点标签颜色
    line->setPointLabelsFont(QFont("黑体"));       //点标签字体
    line->setPointLabelsFormat("(@xPoint,@yPoint)");   //点标签格式
    line->setPointLabelsClipping(true);       //是否切割边缘点标签，默认为true

    connect(line, &QScatterSeries::hovered, this, &LineChartBlockView::on_mouse_entered_line);//设置鼠标移入事件


    lines->append(line);

    if(hasAxis){
        line->append(0,0);
        line->append(0,20);
        chart->addSeries(line);//添加线到QChart上
        chart->createDefaultAxes();
        line->clear();
    }
    else{
        line->append(0,0);
        line->append(0,20);
        chart->addSeries(line);//添加线到QChart上
        chart->createDefaultAxes();
        chart->axisX()->setRange(0,maxX);
        chart->axisY()->setRange(0,maxY);
        line->clear();
        hasAxis = true;
    }

}

void LineChartBlockView::update_line(qreal x, qreal y, int index){

    if(index>=lines->size()||index<0)return;

    std::cout<<"LineChartBlockView::update_line:index:"<<index<<std::endl;
    log_error("Warning Here!!!");
    if(datanum==0){
        minY = (int)(y+0.5)-0.5;
        maxY = (int)(y+0.5)+0.5;
        chart->axisY()->setRange(minY,maxY);
    }
    bool changed = false;
    if(y<=minY)
    {
        minY=(int)(y+0.5)-1;
        changed = true;
    }
    if(y>=maxY)
    {
        maxY=(int)(y+0.5)+1;
        changed = true;
    }
    if(changed){
        chart->axisY()->setRange(minY,maxY);
    }

    QLineSeries* target = lines->at(index);
    if(datanum>=20){
        target->remove(0);
        chart->axisX()->setRange(datanum-19, datanum+1);
    }
    datanum++;
    *target << QPointF(x, y);
    chart->update();
}

void LineChartBlockView::data_added(){
    datanum++;
}

void LineChartBlockView::on_mouse_entered_line(const QPointF &point, bool state){
    QLineSeries* line = qobject_cast<QLineSeries *>(sender());
    if(state){
        //line->setPointLabelsVisible(true);
        line->setPen(QPen(line->pen().brush(),2,Qt::SolidLine));
    }
    else{
        //line->setPointLabelsVisible(false);
        line->setPen(QPen(line->pen().brush(),1,Qt::SolidLine));
    }
    chart->update();
}

void LineChartBlockView::mouseReleaseEvent(QMouseEvent *event){
    emit enlarge(this);
    //qDebug()<<"aaa";
}
