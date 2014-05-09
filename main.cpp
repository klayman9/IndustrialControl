#include <QtGui/QApplication>
#include <QDebug>

#include <QTextCodec>

#include "industrial_control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("KOI8-R"));

    industrial_control w;
    qDebug() << "Hell yaeh";
    w.show();
    return a.exec();
}
