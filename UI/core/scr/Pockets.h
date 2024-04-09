#pragma once
#include <QString>
#include <QUdpSocket>

#define COMMAND_GET_INDICATORS_COUNT 0xA1A20000
#define COMMAND_GET_STAT             0xA1A20001
#define COMMAND_INDIC_ACTION_ON      0xA1A20002
#define COMMAND_INDIC_ACTION_OFF     0xA1A20003

enum class PocketsTypes {
    INDICATOR_COMMAND,
    INDICATOR_COUNT_PACK,
    INDICATOR_STAT,
    INDICATOR_STAT_PACK
};

class Pocket {
public:
    virtual QByteArray serializeData() const = 0;
    virtual Pocket& deserializeData(QByteArray& bytesData) = 0;
};

// Отправка пакетов для получения информации об устройствах в сети
class sIndicatorCommand : public Pocket {
public:
    QByteArray serializeData() const override;
    Pocket& deserializeData(QByteArray& bytesData) override;
    sIndicatorCommand(quint32 command_, quint32 indicatorIndex_ = -1) : command(command_), indicatorIndex(indicatorIndex_) {}
    sIndicatorCommand() = default;


public:
    quint32 crc32;
    quint32 command;
    quint32 indicatorIndex;

};

class sIndicatorsCountPack : public Pocket {
public:
    QByteArray serializeData() const override;
    Pocket& deserializeData(QByteArray& bytesData) override;
    explicit operator quint32() const { return indicatorsCount; }
public:
    quint32 indicatorsCount;
    quint32 crc32;
    quint32 command;

};

class sOneIndicatorStats : public Pocket {
public:
    QByteArray serializeData() const override;
    Pocket& deserializeData(QByteArray& bytesData) override;

public:
    quint64 serialNumber;
    quint32 type        ;
    quint32 power       ;
    quint32 color       ;
    quint32 current_ma  ;
    quint32 reserve     ;
    quint64 error_code;

};

class sIndicatorStatisticsPack : public Pocket {
public:
    QByteArray serializeData() const override;
    Pocket& deserializeData(QByteArray& bytesData) override;

public:
    quint32 command;
    quint32 indicatorIndex;
    sOneIndicatorStats indicatorData;
    quint32 crc32;

};

class MainPocket {
public:
    QByteArray serializeData() const;
    MainPocket& deserializeData(QByteArray& bytesData);
    MainPocket(QByteArray data_, quint16 command_) : data(data_), command(command_) {}
    MainPocket() = default;

public:
    QByteArray data;
    quint16 command;
};

class SerializeDeserializePocket {
public:
    static QByteArray serializePocket(Pocket& pocket);
    static Pocket& deserializePocket(QByteArray& bytesData, Pocket& pocket);

};

