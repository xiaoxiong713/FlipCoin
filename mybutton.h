#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:

    MyButton(QString normalimg, QString pressimg = "");
    QString normalPath;
    QString pressPath;

    //向下跳跃
    void zoomDown();

    //向上跳跃
    void zoomUp();


    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYBUTTON_H
