#pragma once
#include <QtNetwork>
#include "Packets.h"
#include <iostream>

const QString ADDRES = "127.0.0.1";
const int PORT = 8000;

class MyUdpServer : public QObject
{
    Q_OBJECT

public:
    MyUdpServer(QObject *parent = nullptr) : QObject(parent)
    {
        std::cout << "Server initialized\n";
        serverSocket = new QUdpSocket(this);

        if (!serverSocket->bind(QHostAddress::LocalHost, PORT)) {
            std::cerr << "Failed to bind to port " << PORT << std::endl;
            return;
        }
        std::cout << "Bound to port " << PORT << std::endl;

        connect(serverSocket, &QUdpSocket::readyRead, this, &MyUdpServer::processPendingDatagrams);

        // Start a timer to send updated values every second
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyUdpServer::sendUpdatedValues);
        timer->start(1000); // Interval: 1000 milliseconds (1 second)
        std::cout << "Timer started\n";
    }

private slots:
    void processPendingDatagrams()
    {
        while (serverSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(serverSocket->pendingDatagramSize());

            serverSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            // Process incoming datagrams if needed
        }
    }

    void sendUpdatedValues()
    {


        MainPacket sendPacket2;

        sendPacket2.command = COMMAND_GET_STAT;
        sIndicatorStatisticsPack stat;
        stat.indicatorData.current_ma = std::rand() % 100;
        stat.indicatorData.color = std::rand() % 3;
        stat.indicatorData.serialNumber = std::rand() % (100000000 - 10000000 + 1) + 10000000;
        sendPacket2.data = SerializeDeserializePacket::serializePacket(stat);
        auto data2 = sendPacket2.serializeData();
        serverSocket->writeDatagram(data2, sender, senderPort);

        std::cout << "Sending updated values\n";
        // Create and send the packet with updated values
        MainPacket sendPacket;
        sendPacket.command = COMMAND_GET_INDICATORS_COUNT;
        sIndicatorsCountPack counts;
        counts.indicatorsCount = std::rand() % 10;
        sendPacket.data = SerializeDeserializePacket::serializePacket(counts);
        auto data = sendPacket.serializeData();
        serverSocket->writeDatagram(data, sender, senderPort);
    }


private:
    QUdpSocket *serverSocket;
    QHostAddress sender;
    quint16 senderPort;
};

