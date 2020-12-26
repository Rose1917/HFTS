#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    // 绘图
    void loadStyleSheet(QString name);
    void paintContent();                                // 绘制主界面内容
    void initTitle();                                   // 无标题框风格

    // 需要重写的事件
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // 使用QSS中的widget子类的background必须重写paintEvent
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Login *ui;

    QLabel *welcome;                // 上方装饰用
    QLabel *headImg;                // 头像

    // 用户名正则表达式
    QRegExpValidator *userREV;

    QLineEdit *userInput;
    QLineEdit *passwdInput;
    QLabel *userLabel;
    QLabel *passwdLabel;

    QPushButton *signInButton;
    QLabel *tips;                   // 忘记密码或注册账号

    QLabel *failTips;               // 登陆失败提示信息

    QHBoxLayout *titleLayout;       // 标题栏
    QLabel *titleLabel;             // 标题
    QLabel *iconLabel;              // 图标
    QPushButton *minimizeButton;    // 最小化按钮
    QPushButton *closeButton;       // 关闭按钮

    QFormLayout *inputLayout;       // 输入用户名密码布局
    QHBoxLayout *HLayout;           // 调整水平方向
    QVBoxLayout *formLayout;        // 中间的表单布局
    QVBoxLayout *mainLayout;        // 主布局

    // 事件通信
    bool isPressed;
    QPoint startPos;

public slots:
    void signIn();
};
#endif // LOGIN_H
