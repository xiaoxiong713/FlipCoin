#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation> //创建动画对象 ， 头文件


//函数的声明和函数的实现体中，不能同时有默认参数
MyButton::MyButton(QString normalimg, QString pressimg)
{
    this->normalPath = normalimg;
    this->pressPath = pressimg;

    QPixmap pix;
    bool ret = pix.load(this->normalPath);

    if(!ret)
    {
        QString str = QString("参数有误, 失败的路径是：%1").arg(this->normalPath);
        qDebug() << str;
    }

    //设置按钮的固定尺寸
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则的样式
    this->setStyleSheet("QPushButton{border: 0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyButton::zoomDown()
{
    QPropertyAnimation * anima = new QPropertyAnimation(this, "geometry");
    anima->setDuration(200);
    anima->setStartValue( QRect(this->x(), this->y(), this->width(), this->height()) );
    anima->setEndValue( QRect(this->x(), this->y() + 10, this->width(), this->height()) );
    anima->setEasingCurve(QEasingCurve::OutBounce);
    anima->start(QAbstractAnimation::DeleteWhenStopped);

//    QAbstractAnimation::KeepWhenStopped       The animation will not be deleted when stopped.
//    QAbstractAnimation::DeleteWhenStopped     The animation will be automatically deleted when stopped
}

void MyButton::zoomUp()
{
    QPropertyAnimation * anima = new QPropertyAnimation(this, "geometry");
    anima->setDuration(200);
    anima->setStartValue( QRect(this->x(), this->y() + 10, this->width(), this->height()) );
    anima->setEndValue( QRect(this->x(), this->y(), this->width(), this->height()) );
    anima->setEasingCurve(QEasingCurve::OutBounce);
    anima->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    //第二个参数 pressPath， 不为空， 才切图
    if(this->pressPath != "")
    {
        //以下代码可以封装起来， 上面有重复
        QPixmap pix;
        bool ret = pix.load(this->pressPath);

        if(!ret)
        {
            QString str = QString("参数有误, 失败的路径是：%1").arg(this->pressPath);
            qDebug() << str;
        }

        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则的样式
        this->setStyleSheet("QPushButton{border: 0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //其他的事情交给父类处理
    QPushButton::mousePressEvent(e);


}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    //第二个参数 pressPath， 不为空， 才切图
    if(this->pressPath != "")
    {
        //以下代码可以封装起来， 上面有重复
        QPixmap pix;
        bool ret = pix.load(this->normalPath);

        if(!ret)
        {
            QString str = QString("参数有误, 失败的路径是：%1").arg(this->normalPath);
            qDebug() << str;
        }

        //设置按钮的固定尺寸
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则的样式
        this->setStyleSheet("QPushButton{border: 0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //其他的事情交给父类处理
    QPushButton::mouseReleaseEvent(e);
}























