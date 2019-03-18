#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void initUI();
    void addEvents();
    void removeEvents();

private slots:
    void onClickCapture();

private:
    QWidget *mainWidget = Q_NULLPTR;
    QPushButton * btnCapture = Q_NULLPTR;
    QAction * action = Q_NULLPTR;
};

#endif // MAINWINDOW_H
