#include "../include/Packets.h"

QByteArray sIndicatorCommand::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << crc32 << indicatorIndex << command;
    return bytesData;
}

Packet& sIndicatorCommand::deserializeData(QByteArray& bytesData) {
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

Packet& sIndicatorsCountPack::deserializeData(QByteArray& bytesData) {
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

Packet& sOneIndicatorStats::deserializeData(QByteArray& bytesData) {
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

Packet& sIndicatorStatisticsPack::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    QByteArray data;
    dataStream >> command >> indicatorIndex >> data >> crc32;
    indicatorData.deserializeData(data);
    return *this;
}

QByteArray MainPacket::serializeData() const {
    QByteArray bytesData;
    QDataStream dataStream(&bytesData, QIODevice::WriteOnly);
    dataStream << data << command;
    return bytesData;
}

MainPacket& MainPacket::deserializeData(QByteArray& bytesData) {
    QDataStream dataStream(&bytesData, QIODevice::ReadOnly);
    dataStream >> data >> command;
    return *this;
}


QByteArray SerializeDeserializePacket::serializePacket(Packet& packet) {
    return packet.serializeData();
}

Packet& SerializeDeserializePacket::deserializePacket(QByteArray& bytesData, Packet& packet) {
    return packet.deserializeData(bytesData);
}
