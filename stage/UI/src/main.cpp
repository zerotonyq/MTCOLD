#include "../include/mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QThread>
#include "../../Core/include/TestServer.h"

class ServerThread : public QThread
{
Q_OBJECT

protected:
    void run() override
    {
        MyUdpServer server;
        exec(); // This starts the event loop for the thread
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    ServerThread serverThread;
    serverThread.start(); // Start the server thread

    w.show();

    int result = a.exec();

    serverThread.quit(); // Signal the thread to quit
    serverThread.wait(); // Wait for the thread to finish

    return result;
}

#include "main.moc"  // Add this line to include the moc file
