/*Стабільний коміт 23.05.2022*/
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStringList args = a.arguments();
    //if (args.count() != 2)
    //{
        //std::cerr << "argument required" << endl;
        //return 1;
    //qDebug() << args;
    //}
    if (args.count() == 2)
        w.setFileNameCommandLine(QString(args[1]));

    w.show();
    return a.exec();
}

