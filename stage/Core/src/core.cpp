#include "../include/core.h"

Core::Core() : socket(new QUdpSocket) {
    socket->connectToHost(QHostAddress::LocalHost, currentPort);
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

MainPocket Core::sendRecievePocket(Pocket& sendPocket, quint16 command) {
    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(sendPocket), command);
    socket->writeDatagram(sendMainPocket.serializeData());

    MainPocket receiveMainPocket;
    QObject::connect(socket, &QUdpSocket::readyRead, [&](){
        while (socket->hasPendingDatagrams()) {
            QByteArray receiveData;
            receiveData.resize(socket->pendingDatagramSize());
            socket->readDatagram(receiveData.data(), receiveData.size());
            receiveMainPocket.deserializeData(receiveData);
            qDebug() << receiveMainPocket.command;
        }
    });
    return receiveMainPocket;
}

sIndicatorsCountPack Core::getIndicatorsQuantity() {
    sIndicatorCommand indicatorCommand(COMMAND_GET_INDICATORS_COUNT);
    MainPocket replyFromServer = sendRecievePocket(indicatorCommand, static_cast<quint16>(COMMAND_GET_INDICATORS_COUNT));

    sIndicatorsCountPack indocatorsCount;
    SerializeDeserializePocket::deserializePocket(replyFromServer.data, indocatorsCount);
    return indocatorsCount;
}

sIndicatorStatisticsPack Core::getIndicatorStat(quint16 indicatorIndex) {
    sIndicatorCommand indicatorCommand(COMMAND_GET_STAT, indicatorIndex);
    MainPocket replyFromServer = sendRecievePocket(indicatorCommand, static_cast<quint16>(COMMAND_GET_STAT));

    sIndicatorStatisticsPack statisticPack;
    SerializeDeserializePocket::deserializePocket(replyFromServer.data, statisticPack);
    return statisticPack;
}

void Core::sendPocket(Pocket& pocket, quint16 command) {
    MainPocket sendPocket(SerializeDeserializePocket::serializePocket(pocket), command);
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


