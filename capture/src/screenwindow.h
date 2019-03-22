#ifndef SCREENWINDOW_H
#define SCREENWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QAction>
#include <QRect>

class ScreenWindow: public QWidget
{
public:
    ScreenWindow(int screen, QPixmap *pixMap = Q_NULLPTR);
    ~ScreenWindow();
    void paintEvent(QPaintEvent *e);

private:
    void initUI(int screen);
    void addEvents();
    void removeEvents();

private slots:
    void onPressEsc();

private:
    QPixmap *desktopPixMap = Q_NULLPTR;
    QPixmap screenPixMap;
    QAction *pAction = Q_NULLPTR;
    QRect rect;
};

#endif // SCREENWINDOW_H
