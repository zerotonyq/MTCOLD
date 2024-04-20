#pragma once
#include "../../Core/include/core.h"
#include <QString>

class ConnectCore{
public:
    ConnectCore(QString& ip, const quint16 port): core(ip, port){}
    void changeAddress (QString& newIP, const quint16 newPort);
    void turnOnIndicator(quint16 indicatorIndex);
    void turnOffIndicator(quint16 indicatorIndex);
    void getStats(quint16 indicatorIndex);

    QString getIndicatorsSerialNumber(quint16 indicatorIndex);
    QString getIndicatorsType (quint16 indicatorIndex);
    QString getIndicatorsPower (quint16 indicatorIndex);
    QString getIndicatorsColor (quint16 indicatorIndex);
    QString getIndicatorsCurrentMA (quint16 indicatorIndex);
    QString getIndicatorsReserve (quint16 indicatorIndex);
    QString getIndicatorsErrorCode (quint16 indicatorIndex);
    quint32 getIndicatorsQuantity();

private:
    Core core;
    quint32 indicatorsCount;
    quint64 SerialNumber   ;
    quint32 type           ;
    quint32 power          ;
    quint32 color          ;
    quint32 current_ma     ;
    quint32 reserve        ;
    quint64 error_code     ;

};
