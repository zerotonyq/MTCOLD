#pragma once
#include <QtNetwork>
#include "Pockets.h"

class Core {
public:
    Core();
    Core(const QString& addres, const quint16 port);
    ~Core();
    MainPocket sendRecievePocket(Pocket& sendPocket, quint16 command);
    void sendPocket(Pocket& pocket, quint16 command);
    void changeAddres(const QString& newAddr, const quint16 newPort);
    sIndicatorsCountPack getIndicatorsQuantity();
    sIndicatorStatisticsPack getIndicatorStat(quint16 indicatorIndex);
    void turnOnIndicator(quint16 indicatorIndex);
    void turnOffIndicator(quint16 indicatorIndex);

private:
    QString currentAddres = "127.0.0.1";
    quint16 currentPort = 8000;
    QUdpSocket* socket;
};

