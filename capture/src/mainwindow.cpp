#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>
#include <QBoxLayout>
#include <QString>
#include <QTime>
#include <QClipboard>
#include <QMessageBox>
#include <QKeySequence>
#include <QScreen>
#include <QList>
#include "mainwindow.h"
#include "screenwindow.h"

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
    setMinimumSize(400, 300);

    btnCapture = new QPushButton;
    btnCapture->setText(tr("开始截屏"));
    btnCapture->setEnabled(true);
    btnCapture->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(btnCapture);
    mainLayout->setContentsMargins(120, 120, 120, 120);
    mainLayout->setSpacing(20);

    action = new QAction(this);
    // Command + P
    action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    btnCapture->addAction(action);

    mainWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    removeEvents();
}

void MainWindow::addEvents() {
    connect(btnCapture, &QPushButton::clicked, this, &MainWindow::onClickCapture);
    connect(action, &QAction::triggered, this, &MainWindow::onClickCapture);
}

void MainWindow::removeEvents() {
    disconnect(btnCapture, &QPushButton::clicked, this, &MainWindow::onClickCapture);
    disconnect(action, &QAction::triggered, this, &MainWindow::onClickCapture);
}

void MainWindow::onClickCapture() {
    QList<QScreen *> screenList = QGuiApplication::screens();
    QDesktopWidget * desktop = QApplication::desktop();
    for (int i = 0; i< desktop->screenCount(); i++) {
        QWidget * screen = desktop->screen(i);
        QRect rect = desktop->screenGeometry(i);
        QWidget * childWin = new QWidget(screen);
        childWin->setMinimumSize(rect.width(), rect.height());
        childWin->setGeometry(desktop->screenGeometry(i));
        childWin->showFullScreen();
        //childWin->show();
    }

//    int currenMonitor = desktop->screenNumber(this);
//    QRect rect = desktop->screenGeometry(currenMonitor);
//    QScreen * screen = QGuiApplication::primaryScreen();
//    bool result = screen->grabWindow(desktop->winId(), rect.x(), rect.y(), rect.width(), rect.height()).save("/Users/flavor/tmp/001.jpg");
//    printf("onClickCapture=======%d\n", result);

    // width: 1680, height:1050 大屏幕
    // width: 1280, height:800 mac book pro
}
