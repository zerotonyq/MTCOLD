#include "../include/core.h"

Core::Core() : socket(new QUdpSocket) {
    socket->connectToHost(QHostAddress::LocalHost, currentPort);
}

Core::Core(const QString& addres, const quint16 port) : socket(new QUdpSocket) {
    socket->connectToHost(QHostAddress(addres), port);
    currentAddres = addres;
    currentPort = port;
}

Core::~Core() {
    socket->disconnectFromHost();
    delete socket;
}

void Core::changeAddres(const QString& newAddr, const quint16 newPort) {
    socket->disconnectFromHost();
    socket->connectToHost(QHostAddress(newAddr), newPort);
    currentAddres = newAddr;
    currentPort = newPort;
}

MainPacket Core::sendRecievePacket(Packet& sendPocket, quint32 command) {
    MainPacket sendMainPocket(SerializeDeserializePacket::serializePacket(sendPocket), command);
    socket->writeDatagram(sendMainPocket.serializeData());

    MainPacket receiveMainPocket;

    QEventLoop loop;
    QObject::connect(socket, &QUdpSocket::readyRead, [&](){
        while (socket->hasPendingDatagrams()) {
            QByteArray receiveData;
            receiveData.resize(socket->pendingDatagramSize());
            socket->readDatagram(receiveData.data(), receiveData.size());
            receiveMainPocket.deserializeData(receiveData);
            loop.quit();
        }
    });
    loop.exec();
    return receiveMainPocket;
}

sIndicatorsCountPack Core::getIndicatorsQuantity() {
    sIndicatorCommand indicatorCommand(COMMAND_GET_INDICATORS_COUNT);
    MainPacket replyFromServer = sendRecievePacket(indicatorCommand, static_cast<quint32>(COMMAND_GET_INDICATORS_COUNT));

    sIndicatorsCountPack indicatorsCount;
    SerializeDeserializePacket::deserializePacket(replyFromServer.data, indicatorsCount);
    return indicatorsCount;
}

sIndicatorStatisticsPack Core::getIndicatorStat(quint32 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_GET_STAT, indicatorIndex);
    MainPacket replyFromServer = sendRecievePacket(indicatorCommand, static_cast<quint32>(COMMAND_GET_STAT));

    sIndicatorStatisticsPack statisticPack;
    SerializeDeserializePacket::deserializePacket(replyFromServer.data, statisticPack);
    return statisticPack;
}

void Core::sendPacket(Packet& packet, quint32 command) {
    MainPacket sendPacket(SerializeDeserializePacket::serializePacket(packet), command);
    socket->writeDatagram(sendPacket.serializeData());
}

void Core::turnOnIndicator(quint32 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_ON, indicatorIndex);
    sendPacket(indicatorCommand, static_cast<quint32>(COMMAND_INDIC_ACTION_ON));
}

void Core::turnOffIndicator(quint32 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_OFF, indicatorIndex);
    sendPacket(indicatorCommand, static_cast<quint32>(COMMAND_INDIC_ACTION_OFF));
}


