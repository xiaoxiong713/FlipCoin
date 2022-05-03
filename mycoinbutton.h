#ifndef MYCOINBUTTON_H
#define MYCOINBUTTON_H

#include <QPushButton>
#include <QTimer>
class MyCoinButton : public QPushButton
{
    Q_OBJECT
public:
    MyCoinButton(QString imgPath);

    void changeFlag();//执行翻转效果
    QTimer * t1;//定时器， 正面翻反面
    QTimer * t2;//反之
    int min = 1;
    int max = 8;//图标标志位置

    int x;
    int y;
    bool flag;//正反标志

    bool isAnimation = false;// 正在做翻转动画 标志
    void mousePressEvent(QMouseEvent *e);

    bool isWin = false;//游戏胜利标志位， 用于胜利后，屏蔽点击事件
signals:

};

#endif // MYCOINBUTTON_H
