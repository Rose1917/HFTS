#ifndef DATAPAGEITEMINPUT_H
#define DATAPAGEITEMINPUT_H

#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QBoxLayout>
class datapageiteminput : public QWidget
{
    Q_OBJECT
private:
    QLabel* label_name;
    QLineEdit* lineedit_name;

    QHBoxLayout* namelayout;

    QPushButton* submit;
    QVBoxLayout* mainlayout;

public:
    QString getname();
    void setname(QString n);
    datapageiteminput();
signals:
    void on_submit();
private slots:
    void on_submit_clicked();
};
#endif // DATAPAGEITEMINPUT_H
