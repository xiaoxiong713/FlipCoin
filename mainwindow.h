#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void paintEvent(QPaintEvent *event);

    //维护一个第二场景的指针
    ChooseLevelScene * chooseScene;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
