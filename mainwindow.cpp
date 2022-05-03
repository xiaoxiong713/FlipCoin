#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //准备音效
    QSound * startMusic = new QSound(":/src/TapButtonSound.wav", this);
//    startMusic->setLoops(5);//循环播放，指定次数， 无限循环，指定-1
//    startMusic->play();

    connect(ui->actionExit, &QAction::triggered, [=](){
        this->close();
    });

    this->setFixedSize(420, 688);
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/src/Coin0001.png"));//传Qpixmap也可以

    //创建开始按钮
    MyButton * startBtn = new MyButton(":/src/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move((this->width() - startBtn->width()) *0.5, this->height() * 0.7);
    //监听开始按钮
    connect(startBtn, &MyButton::clicked, [=](){
        //按钮点击音效
        startMusic->play();
        qDebug() << "进入选关的环节";
        startBtn->zoomDown();
        startBtn->zoomUp();

        //延时进入第二个场景
        QTimer::singleShot(300, this, [=](){
            this->chooseScene->setGeometry(this->geometry());//  解决： 两个窗口在同一个位置展示
            this->chooseScene->show();//第二页面展示， 第一页面隐藏
            this->hide();

        });
    });

    //初始化第二场景指针
    this->chooseScene = new ChooseLevelScene;

    //监听返回第一场景
    connect(this->chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
            this->setGeometry(this->chooseScene->geometry());//解决： 两个窗口在同一个位置展示
            this->show();
            this->chooseScene->hide();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix;
    pix.load(":/src/PlayLevelSceneBg.png");
    p.drawPixmap(0, 0,this->width(), this->height(), pix);//中间的宽高，是拉伸铺满

    pix.load(":/src/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    p.drawPixmap( 50, 50, pix);


}

