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
#include <QGuiApplication>
#include <QScreen>
#include <QList>
#include "mainwindow.h"
#include "screenwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      mainWidget(Q_NULLPTR),
      btnCapture(Q_NULLPTR)
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
    QDesktopWidget * pDesktop = QApplication::desktop();
    QScreen * pScreen = QGuiApplication::primaryScreen();
    screenPixMap = pScreen->grabWindow(pDesktop->winId(), 0, 0, pDesktop->width(), pDesktop->height());
    QList<QScreen *> result = QGuiApplication::screens();
    for (QList<QScreen *>::const_iterator it = result.constBegin(); it != result.constEnd(); ++it) {
        ScreenWindow * chidWin = new ScreenWindow(*it, &screenPixMap);
        chidWin->setWindowFlag(Qt::FramelessWindowHint, true);
        chidWin->setWindowModality(Qt::ApplicationModal);
        chidWin->setAttribute(Qt::WA_TranslucentBackground, true);
        chidWin->show();
//        chidWin->showFullScreen();
//        chidWin->showMaximized();
    }
}
