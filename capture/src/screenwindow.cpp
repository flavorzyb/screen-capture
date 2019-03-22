#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QWindow>
#include "screenwindow.h"


ScreenWindow::ScreenWindow(int screen, QPixmap *pixMap):
    QWidget (Q_NULLPTR),
    desktopPixMap(pixMap),
    pAction(Q_NULLPTR)
{
    QDesktopWidget *pDesktop = QApplication::desktop();
    if (screen < 0) {
        screen = 0;
    } else if (screen >= pDesktop->screenCount()) {
        screen = pDesktop->screenCount() - 1;
    }

    initUI(screen);
    addEvents();
}

ScreenWindow::~ScreenWindow()
{
    removeEvents();
}

void ScreenWindow::initUI(int screen)
{
    QDesktopWidget *pDesktop = QApplication::desktop();
    rect = pDesktop->screenGeometry(screen);
    setMinimumSize(rect.width(), rect.height());
    setGeometry(rect);

    screenPixMap = desktopPixMap->copy(rect.x() * 2, rect.y() * 2, rect.width() * 2, rect.height() * 2);
//    printf("rect.x====%d, rect.y=====%d, pScreen.devicePixelRatio===%f, pixMap.width=====%d, pixMap.height=======%d\n", rect.x(), rect.y(), pScreen->devicePixelRatio(), pixMap.width(), pixMap.height());
//    QString fileName = "/Users/flavor/tmp/screen_";
//    char str[32] = "";
//    sprintf(str, "%d", screen);
//    fileName.append(str);
//    fileName.append(".png");
//    pixMap.save(fileName, "png", 100);

    pAction = new QAction(this);
    pAction->setShortcut(QKeySequence(Qt::Key_Escape));
    addAction(pAction);
}

void ScreenWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, rect.width() , rect.height(), screenPixMap);
}

void ScreenWindow::addEvents() {
    connect(pAction, &QAction::triggered, this, &ScreenWindow::onPressEsc);
}

void ScreenWindow::removeEvents() {
    disconnect(pAction, &QAction::triggered, this, &ScreenWindow::onPressEsc);
    printf("ScreenWindow::removeEvents======\n");
}

void ScreenWindow::onPressEsc() {
    close();
}

