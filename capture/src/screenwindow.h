#ifndef SCREENWINDOW_H
#define SCREENWINDOW_H

#include <QWindow>
#include <QScreen>

class ScreenWindow: QWindow
{
public:
    ScreenWindow(QScreen *targetScreen = nullptr);
    ~ScreenWindow();

private:
    void initUI();
};

#endif // SCREENWINDOW_H
