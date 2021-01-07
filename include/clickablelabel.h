#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include<QMouseEvent>
#include<QLabel>
class clickablelabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickablelabel( const QString& text="", QWidget* parent=0 );

signals:
    void clicked();
protected:
    virtual void mouseReleaseEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
