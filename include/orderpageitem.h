#ifndef ORDERPAGEITEM_H
#define ORDERPAGEITEM_H

#include<QFrame>
#include<QBoxLayout>
#include<QLabel>
#include<clickablelabel.h>

class orderpageitem : public QFrame
{
    Q_OBJECT
public:
    orderpageitem();
private:
    QLabel* name;
    QLabel* time;

    clickablelabel* maxinumlabel;
    clickablelabel* deletelabel;

    QHBoxLayout* mainlayout;
    QHBoxLayout* toollayout;
    QVBoxLayout* tool_space;
    QHBoxLayout* itemlayout;
};

#endif // ORDERPAGEITEM_H
