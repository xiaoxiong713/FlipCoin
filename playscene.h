#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoinbutton.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);//有参构造， index 关卡号
    void paintEvent(QPaintEvent *event);

    int levelIndex;//记录关卡号
    int gameArray[4][4];//关卡数据
    bool isWin = true; //检测胜利， 默认是胜利
    MyCoinButton * coinBtn[4][4];//所有硬币的二维数组， 方便找周围的硬币

signals:
    void playSceneBack();
};

#endif // PLAYSCENE_H
