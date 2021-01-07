#ifndef EDITLABEL_H
#define EDITLABEL_H

#include <QLineEdit>
class editlabel : public QLineEdit
{
public:
    editlabel();
protected:
    virtual void mouseDoubleClickEvent ( QMouseEvent * event );
    virtual void focusOutEvent(QFocusEvent *);
};

#endif // EDITLABEL_H
