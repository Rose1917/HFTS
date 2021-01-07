#ifndef NONTITLE_H
#define NONTITLE_H

#include<QWidget>
#include<QPushButton>
#include<QBoxLayout>
#include<QMouseEvent>
#include<QPainter>
#include<QStyleOption>
#include<QDesktopWidget>
#include<QApplication>
class nontitle : public QWidget
{
    Q_OBJECT
public:
    nontitle();
    void setContent(QWidget* w);
    void showincenter();
private:
    bool isPressed;
    QPoint startPos;

    QPushButton* minimizeButton;
    QPushButton* closeButton;
    QHBoxLayout* titleLayout;
    QVBoxLayout* layout;
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_exit();
};

#endif // NONTITLE_H
