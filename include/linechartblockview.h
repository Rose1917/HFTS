#ifndef LINECHARTBLOCKVIEW_H
#define LINECHARTBLOCKVIEW_H

#include<QWidget>
#include<QtCharts>

class LineChartBlockView : public QChartView
{
    Q_OBJECT
public:
    LineChartBlockView(QString name,int maxX,int maxY,int maxSize);

    void add_lineseries(QString name,QPen linePen,QColor pointLabelColor);
    void remove_lineseries();
    void set_linevisible(int index,bool visible);
    void set_pointlabel_visiable(int index,bool visivle);

    void update_line(qreal x,qreal y,int index);
    void data_added();


private:
    int maxX;   //x轴范围t~(t+maxX)
    int minY;
    int maxY;   //y轴范围0~maxY
    int maxSize;//数据超过该值时移动曲线
    int datanum;
    bool hasAxis = false;
    QList<double>* data;

    QValueAxis* X;
    QValueAxis* Y;
    QChart* chart;
    //QLineSeries* line;
    QList<QLineSeries*>* lines;
private slots:
    void on_mouse_entered_line(const QPointF &point, bool state);
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void enlarge(LineChartBlockView* view);
};

#endif // LINECHARTBLOCKVIEW_H
