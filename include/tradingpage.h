﻿#ifndef TRADINGPAGE_H
#define TRADINGPAGE_H

#include<QWidget>
#include<QScrollArea>
#include<QComboBox>
#include"clickablelabel.h"
#include<QBoxLayout>
#include<QPlainTextEdit>
#include"little_stratgymanageitem.h"

class tradingpage : public QWidget
{
    Q_OBJECT
public:
    tradingpage();
    QComboBox* get_stratgyselector();
    QTextEdit* get_recordtext();
private:
    QComboBox* stratgyselector;

    clickablelabel* start;
    clickablelabel* stop;
    clickablelabel* clear;

    QTextEdit* recordtext;

    QVBoxLayout* mainlayout;
    QHBoxLayout* toollayout;
    QHBoxLayout* recordlayout;
signals:
    void signal_start();
    void signal_stop();
private slots:
    void on_start();
    void on_stop();
    void on_clear();
};

#endif // TRADINGPAGE_H