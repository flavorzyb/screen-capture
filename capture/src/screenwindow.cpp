#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QWindow>
#include "screenwindow.h"


ScreenWindow::ScreenWindow(QScreen * screen, QPixmap *pixMap):
    QWidget (Q_NULLPTR),
    desktopPixMap(pixMap),
    pAction(Q_NULLPTR),
    pScreen(screen)
{
    initUI();
    addEvents();
}

ScreenWindow::~ScreenWindow()
{
    removeEvents();
}

void ScreenWindow::initUI()
{
    if (pScreen == Q_NULLPTR) {
        pScreen = QGuiApplication::primaryScreen();
    }

    if (pScreen != Q_NULLPTR) {
        rect = pScreen->availableGeometry();
        setMinimumSize(rect.width(), rect.height());
        setGeometry(rect);

        int ratio = int(pScreen->devicePixelRatio());
        screenPixMap = desktopPixMap->copy(rect.x() * ratio, rect.y() * ratio, rect.width() * ratio, rect.height() * ratio);
//        QString fileName = "/Users/flavor/tmp/screen_";
//        char str[32] = "";
//        fileName.append(str);
//        fileName.append(".png");
//        screenPixMap.save(fileName, "png", 100);
    }

    pAction = new QAction(this);
    pAction->setShortcut(QKeySequence(Qt::Key_Escape));
    addAction(pAction);
}

void ScreenWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    if (pScreen != Q_NULLPTR) {
        painter.drawPixmap(0, 0, rect.width() , rect.height(), screenPixMap);
    }
}

void ScreenWindow::addEvents() {
    connect(pAction, &QAction::triggered, this, &ScreenWindow::onPressEsc);
}

void ScreenWindow::removeEvents() {
    disconnect(pAction, &QAction::triggered, this, &ScreenWindow::onPressEsc);
}

void ScreenWindow::onPressEsc() {
    close();
}

