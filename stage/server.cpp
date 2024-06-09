#include <QCoreApplication>
#include "Core/include/TestServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyUdpServer server;
    return a.exec();
}
