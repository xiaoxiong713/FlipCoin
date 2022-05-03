#include "mycoinbutton.h"
#include <QDebug>

MyCoinButton::MyCoinButton(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);

    if(!ret)
    {
        QString str = QString("图片加载失败： 路径有误:%1").arg(imgPath);
        qDebug() << str << endl;
        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));


    //创建定时器
    this->t1 = new QTimer(this);
    this->t2 = new QTimer(this);

    //开启监听1: 金币  翻到  银币
    connect(this->t1, &QTimer::timeout, [=](){
        //不规则图片加载的流程
        QPixmap pix;
        QString str = QString(":/src/Coin000%1.png").arg(this->min ++);
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("图片加载失败： 路径有误:%1").arg(str);
            qDebug() << str << endl;
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        if(this->min > this->max)
        {
            this->min = 1;
            this->t1->stop();
            this->isAnimation = false;
        }
    });

    //开启监听2： 银币 翻到  金币
    connect(this->t2, &QTimer::timeout, [=](){
        //不规则图片加载的流程
        QPixmap pix;
        QString str = QString(":/src/Coin000%1.png").arg(this->max --);
        bool ret = pix.load(str);
        if(!ret)
        {
            QString str = QString("图片加载失败： 路径有误:%1").arg(str);
            qDebug() << str << endl;
            return;
        }

        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));

        if(this->max < this->min)
        {
            this->max = 8;
            this->t2->stop();
            this->isAnimation = false;
        }
    });

}

void MyCoinButton::changeFlag()
{
    if(this->flag)
    {
        this->t1->start(30);
        this->flag = false;
    }
    else
    {
        this->t2->start(30);
        this->flag = true;
    }

    this->isAnimation = true;
}

void MyCoinButton::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        //正在做动画， 禁用点击事件， 或者， 游戏已经胜利
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }

}
























