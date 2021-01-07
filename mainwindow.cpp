#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linechartblockview.h"
#include "testthread.h"
#include "initwindow.h"
#include <QtCharts>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_window();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init_window(){
    /*
    QColor* selected = new QColor(40,43,59);
    QColor* bg = new QColor(20,22,39);
    QColor* unselected = new QColor(29,31,49);
    */
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(new InitWindow);
    ui->centralwidget->setLayout(layout);
}
