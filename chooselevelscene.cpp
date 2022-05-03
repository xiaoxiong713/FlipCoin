#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent): QMainWindow{parent}
{
    //准备音效
    QSound * selectMusic = new QSound(":/src/TapButtonSound.wav", this);
    QSound * backtMusic = new QSound(":/src/BackButtonSound.wav", this);

    this->setFixedSize(420, 688);
    this->setWindowTitle("选择关卡 - 翻金币");
    this->setWindowIcon(QIcon(":/src/Coin0001.png"));//传Qpixmap也可以

    //练习手动创建菜单栏
    QMenuBar * bar = menuBar();
    this->setMenuBar(bar);
    QMenu * startMenu =  bar->addMenu("开始");
    QAction * ActionExit =  startMenu->addAction("退出");
    connect(ActionExit, &QAction::triggered, [=](){
        this->close();

    });
    //返回按钮
    MyButton * backBtn = new MyButton(":/src/BackButton.png", ":/src/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    connect(backBtn, &MyButton::clicked, [=](){
        backtMusic->play();
        qDebug() << "返回上一个菜单" << endl;

        QTimer::singleShot(300, this, [=](){
            //延时发送， 动画效果
            emit this->chooseSceneBack();
        });

    });

    //创建第二场景的内容， 20个按钮， 五行四列
    for(int i = 0; i < 20; ++ i)
    {
        MyButton * coin = new MyButton(":/src/LevelIcon.png");
        coin->setParent(this);
        qDebug() << coin->width() << endl;
        coin->move(76.5 + (i%4)*70, 175.5 + (i/4)*70 );
        connect(coin, &MyButton::clicked, [=](){
            //绑定点击音效
            selectMusic->play();
            //qDebug() << "you seleced is: " << i+1 << "关卡";
            this->threeScene = new PlayScene(i+1);
            this->threeScene->setGeometry(this->geometry());//解决： 两个窗口在同一个位置展示
            this->threeScene->show();
            this->hide();
            //监听返回第二场景, 指针在哪里创建， 就在哪里监听
            connect(this->threeScene, &PlayScene::playSceneBack, [=](){
                    this->setGeometry(this->threeScene->geometry());//解决： 两个窗口在同一个位置展示
                    this->show();
                    this->threeScene->hide();

                //重点： 第三个场景不做复用， 所以要及时释放
                delete this->threeScene;
                this->threeScene = NULL;

            });
        });

        //coin->setText(QString::number(i + 1)); //文字不能现在在中间
        QLabel * label = new QLabel;
        label->setParent(this);
        label->move(76.5 + (i%4)*70, 175.5 + (i/4)*70 );
        label->setFixedSize(coin->width(), coin->height());
        label->setText(QString::number(i + 1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//设置鼠标穿透
    }



}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix;
    pix.load(":/src/OtherSceneBg.png");
    p.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/src/Title.png");
    p.drawPixmap( (this->width() - pix.width())*0.5, 50, pix);
}

























