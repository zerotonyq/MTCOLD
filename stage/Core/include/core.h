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
    void getIndicatorsQuantity();
    void getIndicatorStat(quint16 indicatorIndex);
    void turnOnIndicator(quint16 indicatorIndex);
    void turnOffIndicator(quint16 indicatorIndex);

signals:
    void getIndicatorsQuantityPacket(const sIndicatorsCountPack& indicatorsCountPack);
    void getIndicatorStatisticPacket(const sIndicatorStatisticsPack& indicatorStatisticsPack);

private slots:
    void pendingData();

private:
    void sendPocket(Packet& pocket, quint32 command);

    QString currentAddres = "127.0.0.1";
    quint16 currentPort   = 8000;
    QUdpSocket* socket;
};

