#ifndef SCREENWINDOW_H
#define SCREENWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QAction>
#include <QScreen>
#include <QRect>

class ScreenWindow: public QWidget
{
public:
    ScreenWindow(QScreen * screen, QPixmap *pixMap = Q_NULLPTR);
    ~ScreenWindow();
    void paintEvent(QPaintEvent *e);

private:
    void initUI();
    void addEvents();
    void removeEvents();

private slots:
    void onPressEsc();

private:
    QPixmap *desktopPixMap = Q_NULLPTR;
    QAction *pAction = Q_NULLPTR;
    QScreen *pScreen = Q_NULLPTR;
    QPixmap screenPixMap;
    QRect rect;
};

#endif // SCREENWINDOW_H
