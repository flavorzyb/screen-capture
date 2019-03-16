#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QBoxLayout>
#include <QString>
#include <QTime>
#include <QClipboard>
#include <QMessageBox>
#include <QScreen>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainWidget(nullptr),
      btnCapture(nullptr)
{
    initUI();
    addEvents();
}

void MainWindow::initUI() {
    mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    setWindowTitle(tr("截屏工具"));
    setMinimumSize(800, 600);

    btnCapture = new QPushButton;
    btnCapture->setText(tr("开始截屏"));
    btnCapture->setEnabled(true);
    btnCapture->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(btnCapture);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    mainWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    removeEvents();
}

void MainWindow::addEvents() {
    connect(btnCapture, SIGNAL(pressed()), this, SLOT(onClickCapture()));
}

void MainWindow::removeEvents() {
    disconnect(btnCapture, SIGNAL(pressed()), this, SLOT(onClickCapture()));
}

void MainWindow::onClickCapture() {
    QDesktopWidget * desktop = QApplication::desktop();
    int currenMonitor = desktop->screenNumber(this);
    QRect rect = desktop->screenGeometry(currenMonitor);
    QScreen * screen = QGuiApplication::primaryScreen();
    bool result = screen->grabWindow(desktop->winId(), rect.x(), rect.y(), rect.width(), rect.height()).save("/Users/flavor/tmp/001.jpg");
    printf("onClickCapture=======%d\n", result);
    printf("currenMonitor=====%d\n", currenMonitor);
    printf("width: %d, height:%d\n", rect.width(), rect.height());

    // width: 1680, height:1050 大屏幕
    // width: 1280, height:800 mac book pro
}
