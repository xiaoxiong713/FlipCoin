#include "mainwindow.h"

#include <QApplication>
//#include "dataconfig.h" //测试数据
//#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


//    //测试配置文件， 查看第一关
//    dataConfig c;
//    //对象中有个容器，包含了各个关卡的数据
//    for(int i = 0; i < 4; ++ i)
//    {
//        for(int j = 0; j < 4; ++ j)
//        {
//            qDebug() <<  c.mData[1][i][j];
//        }
//        qDebug() << endl;//qdebug其实 自带换行符
//    }


    return a.exec();
}
