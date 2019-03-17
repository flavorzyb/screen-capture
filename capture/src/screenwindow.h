#ifndef SCREENWINDOW_H
#define SCREENWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

class ScreenWindow: public QWidget
{
public:
    ScreenWindow(int screen);
    ~ScreenWindow();
    void paintEvent(QPaintEvent *e);
private:
    void initUI(int screen);

private:
    QPixmap pixMap;
};

#endif // SCREENWINDOW_H
