#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mybutton.h"
#include <QTimer>
#include <QLabel>
#include <mycoinbutton.h>
#include "dataconfig.h"
#include <QPropertyAnimation> //创建动画对象 ， 头文件
#include <QSound>

PlayScene::PlayScene(int index)
{
    //准备音效
    QSound * backtMusic = new QSound(":/src/BackButtonSound.wav", this);
    QSound * flipMusic = new QSound(":/src/ConFlipSound.wav", this);
    QSound * winMusic = new QSound(":/src/LevelWinSound.wav", this);


    this->levelIndex = index;
    qDebug() << "您进入的是第： "<< index << "关";
    this->setFixedSize(420, 688);
    this->setWindowTitle(QString("第%1关 - 翻金币").arg(this->levelIndex));
    this->setWindowIcon(QIcon(":/src/Coin0001.png"));
    QMenuBar * bar = menuBar();
    QMenu * startMenu =  bar->addMenu("开始");
    QAction * actionExit = startMenu->addAction("退出");
    connect(actionExit, &QAction::triggered, [=](){
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
            emit this->playSceneBack();
        });

    });
    //在页面显示Level: 20

    QLabel * label = new QLabel;
    label->setParent(this);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);
    QFont font("华文新魏", 20);// == font.setFamily("xxxx")   font.setPointSize(20)
    label->setFont(font);
    //设置大小（fixsized）位置（move）, geometry既可以设置大小， 也可以设置宽高
    label->setGeometry(QRect(30, this->height() - 50, this->width(), 50));
    label->setAttribute(Qt::WA_TransparentForMouseEvents);//鼠标穿透

    //胜利图片预加载
    QLabel  * winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/src/LevelCompletedDialogBg.png");
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->move(this->width()*0.5 - pix.width()*0.5, -pix.height());//居中显示


    //初始化关卡, 从数据文件中获取数据， 对应到每一个按钮， 再根据是1还是0， 添加图片
    dataConfig c;
    for(int i = 0; i < 4; ++ i)
    {
        for(int j = 0; j < 4; ++ j)
        {
            this->gameArray[i][j] =  c.mData[this->levelIndex][i][j];
        }
    }


    //开始写， 第三场景的内容
    for (int i = 0; i < 4; ++ i) {
        for (int j = 0; j < 4; ++ j) {
            //创建格子， 背景图
            QLabel * label = new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/src/BoardNode.png"));
            label->setParent(this);
            label->move(110 + i * 50, 244 + j * 50);


            //创建金币, 填充图片
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/src/Coin0001.png";
            }
            else
            {
                str = ":/src/Coin0008.png";
            }
            MyCoinButton * myCoin = new MyCoinButton(str);
            myCoin->setParent(this);
            myCoin->move(112 + i * 50, 248 + j * 50);
            myCoin->x = i;
            myCoin->y = j;
            myCoin->flag = gameArray[i][j];



            this->coinBtn[i][j] = myCoin;
            //点击事件
            connect(myCoin, &MyCoinButton::clicked, [=](){
                flipMusic->play();
                //禁用所有的点击事件
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        this->coinBtn[i][j]->isWin = true;//屏蔽点击标志位
                    }
                }
                myCoin->changeFlag();
                //gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0;//同步二维数组， 后期存档扩展

                //翻转周围的硬币, 且是 延时效果： 中间先翻转， 周围后翻转
                QTimer::singleShot(300, this, [=](){

                    if(myCoin->x + 1 <= 3)//检测右侧
                    {
                        this->coinBtn[myCoin->x + 1][myCoin->y]->changeFlag();

                    }

                    if(myCoin->x - 1 >= 0)//检测左侧
                    {
                        this->coinBtn[myCoin->x - 1][myCoin->y]->changeFlag();

                    }
                    if(myCoin->y - 1 >= 0)//检测上方
                    {
                        this->coinBtn[myCoin->x][myCoin->y - 1]->changeFlag();

                    }
                    if(myCoin->y + 1 <= 3)//检测下方
                    {
                        this->coinBtn[myCoin->x][myCoin->y + 1]->changeFlag();

                    }
                    //检测游戏是否胜利
                    this->isWin = true;//这个isWin 是场景的， 不是每一个按钮的
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            if(this->coinBtn[i][j]->flag == false)//false代表反面
                            {
                                this->isWin = false;//只要有一个反面， 就不能胜利， 场景标志位设为false
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        winMusic->play();
                        qDebug() << " 游戏胜利，SUCCESS" << endl;

                        //                            for (int i = 0; i < 4; ++i) {
                        //                                for (int j = 0; j < 4; ++j) {
                        //                                    this->coinBtn[i][j]->isWin = true;//所有按钮 屏蔽鼠标事件 标志位
                        //                                }
                        //                            }
                        //将胜利的图片 砸进来
                        QPropertyAnimation * abc =  new QPropertyAnimation(winLabel, "geometry");
                        abc->setDuration(1000);
                        abc->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        abc->setEndValue(QRect(winLabel->x(), winLabel->y() + 200, winLabel->width(), winLabel->height()));
                        abc->setEasingCurve(QEasingCurve::OutBounce);
                        abc->start(QAbstractAnimation::DeleteWhenStopped);//动画结束， 自动释放
                    }
                    else //游戏未胜利
                    {
                        for (int i = 0; i < 4; ++i) {
                            for (int j = 0; j < 4; ++j) {
                                this->coinBtn[i][j]->isWin = false;//取消屏蔽鼠标点击 标志位
                            }
                        }
                    }
                });
            });
        }
    }




}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix;
    pix.load(":/src/PlayLevelSceneBg.png");
    p.drawPixmap(0, 0, this->width(), this->height(), pix);
    pix.load(":/src/Title.png");
    pix = pix.scaled(pix.width()*0.5, pix.height()*0.5);
    p.drawPixmap( 50, 50, pix);
}





















