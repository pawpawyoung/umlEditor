#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
