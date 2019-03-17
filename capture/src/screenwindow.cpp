#include "screenwindow.h"

ScreenWindow::ScreenWindow(QScreen *targetScreen): QWindow (targetScreen)
{
    initUI();
}

ScreenWindow::~ScreenWindow()
{

}

void ScreenWindow::initUI()
{
    setMinimumSize(QSize(800, 600));
}
