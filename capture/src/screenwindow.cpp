#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
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
    QPixmap pixmap = pScreen->grabWindow(pDesktop->winId(), rect.x(), rect.y(), rect.width(), rect.height());
    QString fileName = "/Users/flavor/tmp/screen_";
    char str[32] = "";
    sprintf(str, "%d", screen);
    fileName.append(str);
    fileName.append(".jpg");
    pixmap.save(fileName);
}
