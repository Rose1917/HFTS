#include "login.h"
//#include "ui_login.h"
#include "initwindow.h"
#include "nontitle.h"
#include <QDesktopWidget>
#include "include/main.h"
#include<QApplication>
extern InitWindow* init_window;
Login::Login(QWidget *parent)
    : QWidget(parent)
    //, ui(new Ui::Login)
{
    //ui->setupUi(this);

    // 加载样式表
    QString styleSheetName = ":/qss/stylesheet.css";
    loadStyleSheet(styleSheetName);

    //主界面
    paintContent();

    // 信号槽
    connect(signInButton, SIGNAL(clicked()), this, SLOT(signIn()));
    // 当有输入时，删除failTips的错误提示
    connect(userInput, SIGNAL(textChanged(const QString &)), failTips, SLOT(clear()));
    connect(passwdInput, SIGNAL(textChanged(const QString &)), failTips, SLOT(clear()));
}

Login::~Login()
{
    //delete ui;
}

void Login::loadStyleSheet(QString name){
    // 打开QSS文件
    QFile *qf = new QFile(name);
    if(qf->open(QIODevice::ReadOnly)){
        QString style = QString(qf->readAll());
        this->setStyleSheet(style);
        qf->close();
    }
    else{
        qDebug() << "File open failed.";
    }
}
void Login::paintContent(){
    // 设置大小不可变
    // 如果消除标题栏，则会被覆盖
    this->setFixedSize(480, 420);
    this->setWindowIcon(QIcon(":/img/icon.png"));

    //set the window in the middle of the screen
    QDesktopWidget *screenResolution=QApplication::desktop();
    int appWindowWidth=this->geometry().width();
    int appWindowHeight=this->geometry().height();
    int center_y=screenResolution->height()/2-appWindowHeight/2;
    int center_x=screenResolution->width()/2-appWindowWidth/2;
    this->move(center_x,center_y);

    // 布局
    inputLayout = new QFormLayout();
    formLayout = new QVBoxLayout();
    HLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();

    // 无标题风格
    initTitle();

    // 装饰板块
    welcome = new QLabel("HFTS");
    welcome->setObjectName("welcome");                              // 这是一个QObject属性，未设置时为空字符串，在QSS中会根据此属性进行ID选择
    welcome->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(welcome);

    // 头像
    headImg = new QLabel();
    headImg->setObjectName("headImg");
    headImg->setFixedSize(100, 100);

    mainLayout->addWidget(headImg);
    mainLayout->setAlignment(headImg, Qt::AlignCenter);      // 可以指定布局中的某个部件的对齐方式

    // 输入表单
    userInput = new QLineEdit();
    userInput->setObjectName("userInput");
    userInput->setFixedSize(250, 25);
    userInput->setPlaceholderText("E-mail/Username");
    // 用户名正则
    userREV = new QRegExpValidator(QRegExp("[0-9]{11}|[A-Za-z0-9]+@[A-Za-z0-9]+.[a-z]+"));
    userInput->setValidator(userREV);

    userLabel = new QLabel("user");
    userLabel->setObjectName("userLabel");
    passwdInput = new QLineEdit();
    passwdInput->setObjectName("passwdInput");
    passwdInput->setFixedSize(250, 25);
    passwdInput->setPlaceholderText("Password");
    passwdInput->setEchoMode(QLineEdit::Password);
    passwdLabel = new QLabel("password");
    passwdLabel->setObjectName("passwdLabel");
    // 布局
    formLayout->addSpacing(20);
    inputLayout->setVerticalSpacing(15);
    inputLayout->addRow(userLabel, userInput);
    inputLayout->addRow(passwdLabel, passwdInput);
    formLayout->addLayout(inputLayout);

    // 提示
    tips = new QLabel();
    tips->setObjectName("tips");
    tips->setText("Forget your passwd?<a href='www.baidu.com' style='color:#ffa502'>Click here.<\a>");
    tips->setOpenExternalLinks(true);
    // 布局
    formLayout->addWidget(tips);

    // 登录
    signInButton = new QPushButton("Sign in");
    signInButton->setObjectName("signInButton");
    signInButton->setFixedSize(360, 30);
    // 布局
    formLayout->addWidget(signInButton);

    // 登陆失败
    failTips = new QLabel();
    failTips->setObjectName("failTips");
    failTips->setFixedHeight(20);
    formLayout->addWidget(failTips);

    // 居中显示
    formLayout->setAlignment(inputLayout, Qt::AlignCenter);
    formLayout->setAlignment(signInButton, Qt::AlignCenter);
    formLayout->setAlignment(failTips, Qt::AlignCenter);

    // 对表单的横向处理
    HLayout->addSpacing(40);
    HLayout->addLayout(formLayout);
    HLayout->addSpacing(50);

    // 主布局
    mainLayout->addLayout(HLayout);

    this->setLayout(mainLayout);
}
void Login::initTitle(){
    // 重新绘制
    this->setFixedSize(540, 510);

    // 标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 必须要有，设置背景透明，否则设置圆角会出现白色边角
    this->setAttribute(Qt::WA_TranslucentBackground);
//    titleLabel = new QLabel("High Frequency Trade System");
//    iconLabel = new QLabel();
//    iconLabel->setObjectName("iconLabel");
//    iconLabel->setFixedSize(20, 20);

    minimizeButton = new QPushButton();
    minimizeButton->setObjectName("minimize");
    closeButton = new QPushButton();
    closeButton->setObjectName("close");
    minimizeButton->setIcon(QIcon(":/img/minimizelight.png"));
    closeButton->setIcon(QIcon(":/img/closelight.png"));
    minimizeButton->setFixedSize(26, 26);
    closeButton->setFixedSize(26, 26);
    minimizeButton->setFlat(true);
    closeButton->setFlat(true);

    // 标题栏布局
    titleLayout = new QHBoxLayout();
//    titleLayout->addWidget(iconLabel);
//    titleLayout->addWidget(titleLabel);
    titleLayout->addStretch();
    titleLayout->addWidget(minimizeButton);
    titleLayout->addWidget(closeButton);
    // 修改各部分对齐方式
    titleLayout->setAlignment(iconLabel, Qt::AlignLeft);
//    titleLayout->setAlignment(titleLabel, Qt::AlignLeft);
    titleLayout->setAlignment(closeButton, Qt::AlignRight);
    titleLayout->setAlignment(minimizeButton, Qt::AlignRight);

    mainLayout->addLayout(titleLayout);

    // 连接信号槽 最小化 关闭按钮
    connect(minimizeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}


// 事件
void Login::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Login::mouseMoveEvent(QMouseEvent *event){
    if(isPressed){
        QPoint movePos = event->globalPos() - startPos;
        QPoint widgetPos = this->pos();
        this->move(widgetPos.x() + movePos.x(), widgetPos.y() + movePos.y());

        startPos = event->globalPos();
    }

    // 原事件处理器
    QWidget::mouseMoveEvent(event);
}
void Login::mousePressEvent(QMouseEvent *event){
    isPressed = true;
    startPos = event->globalPos();

    // 原事件处理器
    QWidget::mousePressEvent(event);
}
void Login::mouseReleaseEvent(QMouseEvent *event){
    isPressed = false;

    QWidget::mouseReleaseEvent(event);
}

// 槽函数
void Login::signIn(){
    QString user = userInput->text();
    QString passwd = passwdInput->text();
    qDebug() << user << endl << passwd;

    if(user.isEmpty()){
        userInput->setFocus();
        failTips->clear();
        failTips->setText("You must input the username!");
        return;
    }
    else if(passwd.isEmpty()){
        passwdInput->setFocus();
        failTips->clear();
        failTips->setText("You must input the password!");
        return;
    }


    int res=login_trader(user.toStdString(),passwd.toStdString());
    // TODO 判断用户名密码是否匹配
    if(!res){
        passwdInput->clear();
        failTips->setText("Login success");
        //this->close();
        nontitle* n = new nontitle();
        init_window=new InitWindow();
        main_init();
        n->setContent(init_window);
        n->showincenter();
        //Get into the main menu

    }
    else{
        // 清空密码栏
        passwdInput->clear();
        passwdInput->setFocus();
        failTips->clear();
        failTips->setText("The username or the password is wrong!");
    }
}


