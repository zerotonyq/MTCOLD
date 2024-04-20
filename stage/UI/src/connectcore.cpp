#include "../../UI/include/connectcore.h"

void ConnectCore::changeAddress(QString& newIP, const quint16 newPort){
    core.changeAddres(newIP, newPort);
}

void ConnectCore::turnOnIndicator(quint16 indicatorIndex){
    core.turnOnIndicator(indicatorIndex);
}

void ConnectCore::turnOffIndicator(quint16 indicatorIndex){
    core.turnOffIndicator(indicatorIndex);
}

quint32 ConnectCore::getIndicatorsQuantity(){
    sIndicatorsCountPack count = core.getIndicatorsQuantity();
    indicatorsCount = static_cast<quint32>(count);
    // indicatorsCount = QString::number(sii);
    return indicatorsCount;
}

void ConnectCore::getStats(quint16 indicatorIndex) {
    sIndicatorStatisticsPack statisticPack = core.getIndicatorStat(indicatorIndex);
    SerialNumber = statisticPack.indicatorData.serialNumber;
    type = statisticPack.indicatorData.type;
    power = statisticPack.indicatorData.power;
    color = statisticPack.indicatorData.color;
    current_ma = statisticPack.indicatorData.current_ma;
    reserve = statisticPack.indicatorData.reserve;
    error_code = statisticPack.indicatorData.error_code;
}

QString ConnectCore::getIndicatorsSerialNumber(quint16 indicatorIndex){
    QString StringSerialNumber = QString::number(SerialNumber);
    return StringSerialNumber;
}

QString ConnectCore::getIndicatorsType(quint16 indicatorIndex){
    QString StringType = QString::number(type);
    return StringType;
}

QString ConnectCore::getIndicatorsPower(quint16 indicatorIndex){
    QString StringPower = QString::number(power);
    return StringPower;
}

QString ConnectCore::getIndicatorsColor(quint16 indicatorIndex){
    QString StringColor = QString::number(color);
    return StringColor;
}

QString ConnectCore::getIndicatorsCurrentMA(quint16 indicatorIndex){
    QString StringMA = QString::number(current_ma);
    return StringMA;
}

QString ConnectCore::getIndicatorsReserve(quint16 indicatorIndex){
    QString StringReserve = QString::number(reserve);
    return StringReserve;
}

QString ConnectCore::getIndicatorsErrorCode(quint16 indicatorIndex){
    QString StringError = QString::number(error_code);
    return StringError;
}


