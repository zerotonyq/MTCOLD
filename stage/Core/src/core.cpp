#include "../include/core.h"

Core::Core() : socket(new QUdpSocket(this)) {
    socket->connectToHost(QHostAddress::LocalHost, currentPort);
    connect(socket, &QUdpSocket::readyRead, this, &Core::pendingData);
}

Core::Core(const QString& addres, const quint16 port) {
    socket->connectToHost(QHostAddress(addres), port);
}

Core::~Core() {
    socket->disconnect();
    delete socket;
}

void Core::changeAddres(const QString& newAddr, const quint16 newPort) {
    socket->disconnect();
    socket->connectToHost(QHostAddress(newAddr), newPort);
}

void Core::pendingData() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        MainPacket receivedPacket;
        receivedPacket.deserializeData(datagram);
        if (receivedPacket.command == COMMAND_GET_INDICATORS_COUNT) {
            sIndicatorsCountPack indicatorsCountPack;
            SerializeDeserializePacket::deserializePacket(receivedPacket.data, indicatorsCountPack);
            emit getIndicatorsQuantityPacket(indicatorsCountPack);
        } else if (receivedPacket.command == COMMAND_GET_STAT) {
            sIndicatorStatisticsPack indicatorStatisticsPack;
            SerializeDeserializePacket::deserializePacket(receivedPacket.data, indicatorStatisticsPack);
            emit getIndicatorStatisticPacket(indicatorStatisticsPack);
        }
    }
}

void Core::getIndicatorsQuantity() {
   sIndicatorCommand packetForServer(COMMAND_GET_INDICATORS_COUNT);
   sendPocket(packetForServer, COMMAND_GET_INDICATORS_COUNT);
}

void Core::getIndicatorStat(quint16 indicatorIndex) {
    sIndicatorCommand packetForServer(COMMAND_GET_STAT, indicatorIndex);
    sendPocket(packetForServer, COMMAND_GET_STAT);
}

void Core::sendPocket(Packet& pocket, quint32 command) {
    MainPacket sendPocket(SerializeDeserializePacket::serializePacket(pocket), command);
    socket->writeDatagram(sendPocket.serializeData());
}

void Core::turnOnIndicator(quint16 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_ON, indicatorIndex);
    sendPocket(indicatorCommand, static_cast<quint16>(COMMAND_INDIC_ACTION_ON));
}

void Core::turnOffIndicator(quint16 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_OFF, indicatorIndex);
    sendPocket(indicatorCommand, static_cast<quint16>(COMMAND_INDIC_ACTION_OFF));
}


