#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include "screenwindow.h"


ScreenWindow::ScreenWindow(int screen)
{
    QDesktopWidget *pDesktop = QApplication::desktop();
    if (screen < 0) {
        screen = 0;
    } else if (screen >= pDesktop->screenCount()) {
        screen = pDesktop->screenCount() - 1;
    }

    initUI(screen);
}

ScreenWindow::~ScreenWindow()
{
}

void ScreenWindow::initUI(int screen)
{
    QDesktopWidget *pDesktop = QApplication::desktop();
    QRect rect = pDesktop->screenGeometry(screen);
    setMinimumSize(rect.width(), rect.height());
    setGeometry(rect);

    QScreen * pScreen = QGuiApplication::primaryScreen();
    pixMap = pScreen->grabWindow(pDesktop->winId(), rect.x(), rect.y(), rect.width(), rect.height());
}

void ScreenWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixMap);
}
