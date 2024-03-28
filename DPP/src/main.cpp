#include "../Header_file/mainwindow.h"
#include "../Header_file/core.h"
#include "../Header_file/TestClient.h"
#include "../Header_file/TestServer.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyUdpServer server;
    MyUdpClient client;
    QByteArray data = "Hello!";
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&client, &data](){
        client.sendData(data);
    });

    timer.start(1000);



    return a.exec();
}
