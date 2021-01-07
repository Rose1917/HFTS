#ifndef SPONSORPAGE_H
#define SPONSORPAGE_H

#include<QWidget>
#include<QLabel>
#include<QBoxLayout>

class sponsorpage : public QWidget
{
    Q_OBJECT
public:
    sponsorpage();
private:
    QLabel* icon;
    QVBoxLayout* mainlayout;
};

#endif // SPONSORPAGE_H
