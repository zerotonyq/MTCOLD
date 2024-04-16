#include "../include/Pockets.h"

QByteArray sIndicatorCommand::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << crc32 << indicatorIndex << command;
    return bytesData;
}

Pocket& sIndicatorCommand::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    dataStream >> crc32 >> indicatorIndex >> command;
    return *this;
}

QByteArray sIndicatorsCountPack::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << indicatorsCount << crc32 << command;
    return bytesData;
}

Pocket& sIndicatorsCountPack::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    dataStream >> indicatorsCount >> crc32 >> command;
    return *this;
}

QByteArray sOneIndicatorStats::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << serialNumber << type << power << color << current_ma << reserve << error_code;
    return bytesData;
}

Pocket& sOneIndicatorStats::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    dataStream >> serialNumber >> type >> power >> color >> current_ma >> reserve >> error_code;
    return *this;
}

QByteArray sIndicatorStatisticsPack::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << command << indicatorIndex << indicatorData.serializeData() << crc32;
    return bytesData;
}

Pocket& sIndicatorStatisticsPack::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    QByteArray data;
    dataStream >> command >> indicatorIndex >> data >> crc32;
    indicatorData.deserializeData(data);
    return *this;
}

QByteArray MainPocket::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << data << command;
    return bytesData;
}

MainPocket& MainPocket::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    dataStream >> data >> command;
    return *this;
}


QByteArray SerializeDeserializePocket::serializePocket(Pocket& pocket) {
    return pocket.serializeData();
}

Pocket& SerializeDeserializePocket::deserializePocket(QByteArray& bytesData, Pocket& pocket) {
    return pocket.deserializeData(bytesData);
}
