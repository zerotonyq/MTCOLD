#pragma once
#include <QtNetwork>
#include "Packets.h"

class Core : public QObject {
Q_OBJECT
public:
    Core();
    Core(const QString& addres, const quint16 port);
    ~Core();
    void changeAddres(const QString& newAddr, const quint16 newPort);
    sIndicatorsCountPack getIndicatorsQuantity();
    sIndicatorStatisticsPack getIndicatorStat(quint32 indicatorIndex);
    void turnOnIndicator(quint32 indicatorIndex);
    void turnOffIndicator(quint32 indicatorIndex);

private:
    MainPacket sendRecievePacket(Packet& sendPocket, quint32 command);
    void sendPacket(Packet& packet, quint32 command);

private:
    QString currentAddres = "127.0.0.1";
    quint16 currentPort = 8000;
    QUdpSocket* socket;
};

