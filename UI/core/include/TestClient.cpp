#include <QCoreApplication>
#include <QUdpSocket>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QUdpSocket udpSocket;
    udpSocket.bind(QHostAddress::LocalHost, 8001);

    QByteArray data = "Hello Server!";
    udpSocket.writeDatagram(data, QHostAddress::LocalHost, 8000); // Отправка сообщения серверу

    QObject::connect(&udpSocket, &QUdpSocket::readyRead, [&](){
        while (udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket.pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            qDebug() << "Received response from" << sender.toString() << "port" << senderPort << ":" << datagram;
        }
    });

    return a.exec();
}
