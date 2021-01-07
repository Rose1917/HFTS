#ifndef DATAPAGEITEMDEFAULT_H
#define DATAPAGEITEMDEFAULT_H

#include<QFrame>
#include<QLabel>
#include<QBoxLayout>
#include"clickablelabel.h"
class datapageitemdefault : public QFrame
{
public:
    datapageitemdefault();
    clickablelabel* getlabel();
private:
    clickablelabel* icon;
    QVBoxLayout* mainlayout;
};

#endif // DATAPAGEITEMDEFAULT_H
