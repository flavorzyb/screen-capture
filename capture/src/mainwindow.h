#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
private:
    QWidget *mainWidget = nullptr;
    QPushButton * btnCapture = nullptr;
};

#endif // MAINWINDOW_H
