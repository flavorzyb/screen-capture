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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void addEvents();
    void removeEvents();

private slots:
    void onClickCapture();

private:
    QWidget *mainWidget = nullptr;
    QPushButton * btnCapture = nullptr;
    QAction * action = nullptr;
};

#endif // MAINWINDOW_H
