#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    //第三个场景的指针, 一开始没有new, 当用户点击金币时候在new
    PlayScene *threeScene = NULL;
signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
