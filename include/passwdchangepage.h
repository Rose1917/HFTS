#ifndef PASSWDCHANGE_H
#define PASSWDCHANGE_H

#include<QGridLayout>
#include<QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QBoxLayout>
#include<QPushButton>

class passwdchangepage : public QWidget
{
    Q_OBJECT
public:
    passwdchangepage();
private:
    QLabel* orig_passwd;
    QLabel* new_passwd;
    QLabel* confirm_passwd;

    QLineEdit* edit_orig_passwd;
    QLineEdit* edit_new_passwd;
    QLineEdit* edit_confirm_passwd;

    QGridLayout* inputlayout;
    QVBoxLayout* mainlayout;

    QPushButton* submit;
private slots:
    void on_submit_clicked();
};

#endif // PASSWDCHANGE_H
