#include "../include/mainwindow.h"
#include <QFile>
#include <QApplication>
#include "../../Core/include/TestServer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MyUdpServer server;
    w.show();


    return a.exec();
}
