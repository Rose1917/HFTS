#include "nontitle.h"

nontitle::nontitle()
{
    layout = new QVBoxLayout();
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
//    titleLayout->setAlignment(iconLabel, Qt::AlignLeft);
//    titleLayout->setAlignment(titleLabel, Qt::AlignLeft);
    titleLayout->setAlignment(closeButton, Qt::AlignRight);
    titleLayout->setAlignment(minimizeButton, Qt::AlignRight);

    layout->addLayout(titleLayout);

    this->setLayout(layout);

    // 连接信号槽 最小化 关闭按钮
    connect(minimizeButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void nontitle::setContent(QWidget *w){
    layout->addWidget(w);
}

void nontitle::mouseMoveEvent(QMouseEvent *event){
    if(isPressed){
        QPoint movePos = event->globalPos() - startPos;
        QPoint widgetPos = this->pos();
        this->move(widgetPos.x() + movePos.x(), widgetPos.y() + movePos.y());

        startPos = event->globalPos();
    }

    // 原事件处理器
    QWidget::mouseMoveEvent(event);
}
void nontitle::mousePressEvent(QMouseEvent *event){
    isPressed = true;
    startPos = event->globalPos();

    // 原事件处理器
    QWidget::mousePressEvent(event);
}
void nontitle::mouseReleaseEvent(QMouseEvent *event){
    isPressed = false;

    QWidget::mouseReleaseEvent(event);
}

void nontitle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
    painter.setBrush(QBrush(QPixmap(":/img/backgroundblack.png")));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 16, 16);
    //也可用QPainterPath 绘制代替 painter.drawRoundedRect(rect, 15, 15);

    //QPainterPath painterPath;
    //painterPath.addRoundedRect(rect, 16, 16);
    //painter.drawPath(painterPath);

    QWidget::paintEvent(event);
}

void nontitle::on_exit(){
    this->close();
}

void nontitle::showincenter(){
    QDesktopWidget *deskdop=QApplication::desktop();
    this->show();
    this->move((deskdop->width()-this->width())/2, (deskdop->height()-this->height())/2);
}
