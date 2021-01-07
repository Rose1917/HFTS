#ifndef STRATGYMANAGEITEMDEFAULT_H
#define STRATGYMANAGEITEMDEFAULT_H

#include<QFrame>
#include<QLabel>
#include<QBoxLayout>
#include"clickablelabel.h"
class stratgymanageitemdefault : public QFrame
{
public:
    stratgymanageitemdefault();
    clickablelabel* getlabel();
private:
    clickablelabel* icon;
    QVBoxLayout* mainlayout;
};

#endif // STRATGYMANAGEITEMDEFAULT_H
