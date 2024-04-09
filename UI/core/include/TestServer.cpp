#include <QCoreApplication>
#include <QUdpSocket>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QUdpSocket udpSocket;
    udpSocket.bind(QHostAddress::LocalHost, 8000);

    QObject::connect(&udpSocket, &QUdpSocket::readyRead, [&](){
        while (udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            qDebug() << "Received message from" << sender.toString() << "port" << senderPort << ":" << datagram;

            // Отправляем ответ клиенту
            udpSocket.writeDatagram("Hello from server", sender, senderPort);
        }
    });

    return a.exec();
}
