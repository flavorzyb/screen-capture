#ifndef SCREENWINDOW_H
#define SCREENWINDOW_H

#include <QWidget>
#include <QRect>

class ScreenWindow: public QWidget
{
public:
    ScreenWindow(int screen);
    ~ScreenWindow();

private:
    void initUI(int screen);
};

#endif // SCREENWINDOW_H
