#pragma once
#include <QtNetwork>
#include "core.h"

const QString ADDRES = "127.0.0.1";
const int PORT = 8000;

class MyUdpServer : public QObject
{
    Q_OBJECT

public:
    MyUdpServer(QObject *parent = nullptr) : QObject(parent)
    {
        serverSocket = new QUdpSocket(this);
        serverSocket->bind(QHostAddress::LocalHost, 8000);

        connect(serverSocket, &QUdpSocket::readyRead, this, &MyUdpServer::processPendingDatagrams);
    }

private slots:
    void processPendingDatagrams()
    {
        while (serverSocket->hasPendingDatagrams()) {
            qDebug() << "H  ERE\n";
            QByteArray datagram;
            datagram.resize(serverSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            serverSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            MainPacket sendPacket;
            sendPacket.command = COMMAND_GET_INDICATORS_COUNT;
            sIndicatorsCountPack counts;
            counts.indicatorsCount = 13;
            sendPacket.data = SerializeDeserializePacket::serializePacket(counts);
            auto data = sendPacket.serializeData();

            serverSocket->writeDatagram(data, sender, senderPort);
        }
    }

private:
    QUdpSocket *serverSocket;
};


