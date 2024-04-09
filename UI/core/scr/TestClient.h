#pragma once
#include <QtNetwork>

// const QString ADDRES = "127.0.0.1";
// const int PORT = 8000;

class MyUdpClient : public QObject
{
    Q_OBJECT

public:
    MyUdpClient(QObject *parent = nullptr) : QObject(parent)
    {
        socket = new QUdpSocket(this);
        socket->connectToHost(QHostAddress::LocalHost, 8000);

        connect(socket, &QUdpSocket::readyRead, this, &MyUdpClient::processPendingDatagrams);
    }

    void sendData(QByteArray& data) {
        socket->writeDatagram(data);
    }
    void sendData(QString& data) {
        socket->writeDatagram(data.toUtf8());
    }

private slots:
    void processPendingDatagrams()
    {
        while (socket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(socket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            qDebug() << "Client expect:" << datagram << "from" << sender.toString() << "on port" << senderPort;
        }
    }

private:
    QUdpSocket *socket;
};


