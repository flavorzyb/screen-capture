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
    QRect rect = pDesktop->screenGeometry(screen);
    setMinimumSize(rect.width(), rect.height());
    setGeometry(rect);

    QScreen * pScreen = QGuiApplication::primaryScreen();
    pixMap = pScreen->grabWindow(pDesktop->winId(), rect.x(), rect.y(), rect.width(), rect.height());
    QString fileName = "/Users/flavor/tmp/screen_";
    char str[32] = "";
    sprintf(str, "%d", screen);
    fileName.append(str);
    fileName.append(".jpg");
    pixMap.save(fileName);

    pAction = new QAction(this);
    pAction->setShortcut(QKeySequence(Qt::Key_Escape));
    addAction(pAction);
}

void ScreenWindow::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixMap);
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

