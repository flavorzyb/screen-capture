#include <QDesktopWidget>
#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include <QWindow>
#include "screenwindow.h"


ScreenWindow::ScreenWindow(int screen, QWidget *parent):
    QWidget (parent),
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

    printf("rect.width===%d, rect.height=====%d\n", rect.width(), rect.height());

    QScreen * pScreen = QGuiApplication::primaryScreen();
    pixMap = pScreen->grabWindow(pDesktop->winId(), rect.x(), rect.y(), rect.width() , rect.height());
    printf("rect.x====%d, rect.y=====%d, pScreen.devicePixelRatio===%f, pixMap.width=====%d, pixMap.height=======%d\n", rect.x(), rect.y(), pScreen->devicePixelRatio(), pixMap.width(), pixMap.height());
    //pixMap = pixMap.scaled(rect.width(), rect.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QString fileName = "/Users/flavor/tmp/screen_";
    char str[32] = "";
    sprintf(str, "%d", screen);
    fileName.append(str);
    fileName.append(".png");
    pixMap.save(fileName, "png", 100);

    pAction = new QAction(this);
    pAction->setShortcut(QKeySequence(Qt::Key_Escape));
    addAction(pAction);
}

void ScreenWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);

    painter.drawPixmap(0, 0, rect.width() , rect.height(), pixMap);
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

