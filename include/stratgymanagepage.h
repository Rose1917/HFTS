#ifndef STRATGYMANAGEPAGE_H
#define STRATGYMANAGEPAGE_H

#include<QWidget>
#include<QBoxLayout>
#include<QScrollArea>
#include"nontitle.h"
#include"little_stratgymanageitem.h"
#include"stratgymanageitemdefault.h"
#include"stratgymanageitem.h"
class stratgymanagepage : public QWidget
{
    Q_OBJECT
public:
    stratgymanagepage();
    QList<little_stratgymanageitem*> get_stratgies();
private:
    QVBoxLayout* mainlayout;
    QWidget* items;
    QVBoxLayout* itemslayout;
    QSpacerItem* scrollspacer;

    stratgymanageitemdefault* defaultitem;
    stratgymanageitem* inputitem;

    QList<little_stratgymanageitem*> stratgies;

    nontitle* inputiitemtitle;

private slots:
    void on_add_clicked();
    void on_item_submit();
    void on_delete_item();
    void on_item_stratgy_changed();
signals:
    void stratgy_changed();
};

#endif // STRATGYMANAGEPAGE_H
