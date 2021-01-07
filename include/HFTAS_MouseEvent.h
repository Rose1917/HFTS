#ifndef HTFAS_MOUSEEVENT_H
#define HTFAS_MOUSEEVENT_H

#include<QtCharts>

class HTFAS_MouseEvent
{
    Q_OBJECT
public:
    HTFAS_MouseEvent();

    static void OnMouseEnterLine(const QPointF &point, bool state);
};

#endif // HTFAS_MOUSEEVENT_H
