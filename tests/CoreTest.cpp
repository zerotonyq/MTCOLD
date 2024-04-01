#include "../Header_file/core.h"
#include <QCoreApplication>
#include <QTimer>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

int argcQApp = 1;
const char* argvQApp[] = { "" };

#pragma region ClassesDeclaration

class MockClass {
public:
    MOCK_METHOD(void, MturnOnIndicator, ());
    MOCK_METHOD(void, MturnOnIndicatorArg1, ());
    MOCK_METHOD(void, MturnOnIndicatorArg2, ());

    MOCK_METHOD(void, MturnOffIndicator, ());
    MOCK_METHOD(void, MturnOffIndicatorArg1, ());
    MOCK_METHOD(void, MturnOffIndicatorArg2, ());

    MOCK_METHOD(void, MgetIndicatorsQuantity, ());
    MOCK_METHOD(void, MgetIndicatorsQuantityArg1, ());
    MOCK_METHOD(void, MgetIndicatorsQuantityArg2, ());

    MOCK_METHOD(void, MgetIndicatorStat, ());
    MOCK_METHOD(void, MgetIndicatorStatArg1, ());
    MOCK_METHOD(void, MgetIndicatorStatArg2, ());

    MOCK_METHOD(void, MchangeAddres, ());
    MOCK_METHOD(void, TestMock, ());
};

class CoreTestServer : public QObject {
public:
    MockClass mock;
    CoreTestServer(QObject* parent = nullptr)
        : QObject(parent)
    {
        serverSocket = new QUdpSocket(this);
        serverSocket->bind(QHostAddress::LocalHost, 8000);

        connect(serverSocket, &QUdpSocket::readyRead, this, &CoreTestServer::processPendingDatagrams);
    }
    void changeAddres(const QString& newAddr, const quint16 newPort)
    {
        serverSocket->disconnectFromHost();
        serverSocket->disconnect();
        serverSocket->bind(QHostAddress(newAddr), newPort);
        connect(serverSocket, &QUdpSocket::readyRead, this, &CoreTestServer::processPendingDatagrams);
    }

private slots:
    void processPendingDatagrams()
    {
        while (serverSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(serverSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;

            serverSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            MainPocket receiveMainPocket;
            receiveMainPocket.deserializeData(datagram);

            sIndicatorCommand receiveIndicatorCommand;
            receiveIndicatorCommand.deserializeData(receiveMainPocket.data);
            if (receiveMainPocket.command == static_cast<quint16>(COMMAND_INDIC_ACTION_ON)) {

                if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_INDIC_ACTION_ON) && receiveIndicatorCommand.indicatorIndex == 1)
                    mock.MturnOnIndicatorArg1();
                else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_INDIC_ACTION_ON) && receiveIndicatorCommand.indicatorIndex == 2)
                    mock.MturnOnIndicatorArg2();
                else
                    mock.MturnOnIndicator();
            }
            if (receiveMainPocket.command == static_cast<quint16>(COMMAND_INDIC_ACTION_OFF)) {

                if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_INDIC_ACTION_OFF) && receiveIndicatorCommand.indicatorIndex == 100)
                    mock.MchangeAddres();
                else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_INDIC_ACTION_OFF) && receiveIndicatorCommand.indicatorIndex == 1)
                    mock.MturnOffIndicatorArg1();
                else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_INDIC_ACTION_OFF) && receiveIndicatorCommand.indicatorIndex == 2)
                    mock.MturnOffIndicatorArg2();
                else
                    mock.MturnOffIndicator();
            }
            if (receiveMainPocket.command == static_cast<quint16>(COMMAND_GET_STAT)) {
                if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_GET_STAT) && receiveIndicatorCommand.indicatorIndex == 1) {
                    mock.MgetIndicatorStatArg1();
                    sOneIndicatorStats indicatorData;
                    indicatorData.serialNumber = 3;
                    sIndicatorStatisticsPack Pack;
                    Pack.indicatorData = indicatorData;
                    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_STAT));
                    sIndicatorStatisticsPack statisticPack;
                    SerializeDeserializePocket::deserializePocket(sendMainPocket.data, statisticPack);
                    serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);

                } else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_GET_STAT) && receiveIndicatorCommand.indicatorIndex == 2) {
                    mock.MgetIndicatorStatArg2();
                    sOneIndicatorStats indicatorData;
                    indicatorData.serialNumber = 3;
                    sIndicatorStatisticsPack Pack;
                    Pack.indicatorData = indicatorData;
                    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_STAT));
                    sIndicatorStatisticsPack statisticPack;
                    SerializeDeserializePocket::deserializePocket(sendMainPocket.data, statisticPack);
                    serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);

                } else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_GET_STAT) && receiveIndicatorCommand.indicatorIndex == 3) {
                    sOneIndicatorStats indicatorData;
                    indicatorData.serialNumber = 3;
                    sIndicatorStatisticsPack Pack;
                    Pack.indicatorData = indicatorData;
                    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_STAT));

                    sIndicatorStatisticsPack statisticPack;
                    SerializeDeserializePocket::deserializePocket(sendMainPocket.data, statisticPack);
                    serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);
                } else if (receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_GET_STAT) && receiveIndicatorCommand.indicatorIndex == 4) {
                    sOneIndicatorStats indicatorData;
                    indicatorData.serialNumber = 4;

                    sIndicatorStatisticsPack Pack;
                    Pack.indicatorData = indicatorData;

                    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_STAT));

                    serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);

                } else {
                    mock.MgetIndicatorStat();

                    sOneIndicatorStats indicatorData;
                    indicatorData.serialNumber = 3;
                    sIndicatorStatisticsPack Pack;
                    Pack.indicatorData = indicatorData;
                    MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_STAT));
                    sIndicatorStatisticsPack statisticPack;
                    SerializeDeserializePocket::deserializePocket(sendMainPocket.data, statisticPack);
                    serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);
                }
            }
            if (receiveMainPocket.command == static_cast<quint16>(COMMAND_GET_INDICATORS_COUNT) && receiveIndicatorCommand.command == static_cast<quint32>(COMMAND_GET_INDICATORS_COUNT)) {
                mock.MgetIndicatorsQuantity();
                sIndicatorsCountPack Pack;
                Pack.indicatorsCount = 111;
                MainPocket sendMainPocket(SerializeDeserializePocket::serializePocket(Pack), static_cast<quint16>(COMMAND_GET_INDICATORS_COUNT));
                serverSocket->writeDatagram(sendMainPocket.serializeData(), sender, senderPort);
            }
        }
    }

private:
    QUdpSocket* serverSocket;
};

#pragma endregion ClassesDeclaration

#pragma region sendPocketTest

TEST(sendPocketTest, TestNoArgs)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    Core clientCore;
    CoreTestServer server;
    QTimer::singleShot(10, &a, &QCoreApplication::quit);

    EXPECT_CALL(server.mock, MturnOffIndicator());
    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_OFF, 0);
    clientCore.sendPocket(indicatorCommand, static_cast<quint16>(COMMAND_INDIC_ACTION_OFF));

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(sendPocketTest, TestArg1)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOnIndicatorArg1());

    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_ON, 1);
    clientCore.sendPocket(indicatorCommand, static_cast<quint16>(COMMAND_INDIC_ACTION_ON));

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(sendPocketTest, TestArg2)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOnIndicatorArg2());

    sIndicatorCommand indicatorCommand(COMMAND_INDIC_ACTION_ON, 2);
    clientCore.sendPocket(indicatorCommand, static_cast<quint16>(COMMAND_INDIC_ACTION_ON));

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

#pragma endregion sendPocketTest

#pragma region sendRecievePocketTest

TEST(sendRecievePocketTest, testCommandGetIndicatorsCount)
{
    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorsQuantity());

    sIndicatorsCountPack Pack = clientCore.getIndicatorsQuantity();
    ASSERT_TRUE(static_cast<int>(Pack.indicatorsCount) == 111);
    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(sendRecievePocketTest, testCommandGetStat)
{
    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    quint16 indicatorIndex = 3;
    sIndicatorCommand indicatorCommand(COMMAND_GET_STAT, indicatorIndex);
    MainPocket replyFromServer = clientCore.sendRecievePocket(indicatorCommand, static_cast<quint16>(COMMAND_GET_STAT));

    sIndicatorStatisticsPack statisticPack;
    SerializeDeserializePocket::deserializePocket(replyFromServer.data, statisticPack);
    a.exec();
    ASSERT_TRUE(static_cast<int>(statisticPack.indicatorData.serialNumber) == 3);
}

#pragma endregion sendRecievePocketTest

#pragma region turnOnIndicatorTest

TEST(turnOnIndicatorTest, TestNoArgs)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOnIndicator());

    clientCore.turnOnIndicator(0);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(turnOnIndicatorTest, TestArg1)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOnIndicatorArg1());

    clientCore.turnOnIndicator(1);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(turnOnIndicatorTest, TestArg2)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOnIndicatorArg2());

    clientCore.turnOnIndicator(2);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

#pragma endregion turnOnIndicatorTest

#pragma region turnOffIndicatorTest

TEST(turnOffIndicatorTest, TestNoArgs)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOffIndicator());

    clientCore.turnOffIndicator(0);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(turnOffIndicatorTest, TestArg1)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MturnOffIndicatorArg1());

    clientCore.turnOffIndicator(1);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(turnOffIndicatorTest, TestArg2)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorStatArg2());

    clientCore.getIndicatorStat(2);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

#pragma endregion turnOffIndicatorTest

#pragma region getIndicatorStatTest

TEST(getIndicatorStatTest, TestNoArgs)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorStat());

    clientCore.getIndicatorStat(0);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(getIndicatorStatTest, TestArg1)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorStatArg1());

    clientCore.getIndicatorStat(1);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(getIndicatorStatTest, TestArg2)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorStatArg2());

    clientCore.getIndicatorStat(2);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(getIndicatorStatTest, TestReturn1)
{
    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    sIndicatorStatisticsPack statisticPack = clientCore.getIndicatorStat(3);
    a.exec();
    ASSERT_TRUE(static_cast<int>(statisticPack.indicatorData.serialNumber) == 3);
}

TEST(getIndicatorStatTest, TestReturn2)
{
    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    Core clientCore;
    CoreTestServer server;
    QTimer::singleShot(10, &a, &QCoreApplication::quit);

    sIndicatorStatisticsPack statisticPack = clientCore.getIndicatorStat(4);
    a.exec();
    ASSERT_TRUE(static_cast<int>(statisticPack.indicatorData.serialNumber) == 4);
}

#pragma endregion getIndicatorStatTest

#pragma region changeAddresTest

TEST(changeAddresTest, test1)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    CoreTestServer server;
    Core clientCore;
    EXPECT_CALL(server.mock, MchangeAddres());

    const QString newAddr = "172.24.26.1";
    const int newPort = 8001;

    clientCore.changeAddres(newAddr, newPort);
    server.changeAddres(newAddr, newPort);
    clientCore.turnOffIndicator(100);
    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(changeAddresTest, test2)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    CoreTestServer server;
    Core clientCore;
    EXPECT_CALL(server.mock, MchangeAddres());
    const QString newAddr = "127.0.0.1";
    const int newPort = 8000;
    clientCore.changeAddres(newAddr, newPort);
    server.changeAddres(newAddr, newPort);
    clientCore.turnOffIndicator(100);

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

#pragma endregion changeAddresTest

#pragma region getIndicatorsQuantityTest

TEST(getIndicatorsQuantityTest, getIndicatorsQuantityTest)
{

    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorsQuantity());

    clientCore.getIndicatorsQuantity();

    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

TEST(getIndicatorsQuantityTest, TestReturn1)
{
    QCoreApplication a(argcQApp, const_cast<char**>(argvQApp));
    QTimer::singleShot(10, &a, &QCoreApplication::quit);
    Core clientCore;
    CoreTestServer server;
    EXPECT_CALL(server.mock, MgetIndicatorsQuantity());

    sIndicatorsCountPack Pack = clientCore.getIndicatorsQuantity();
    ASSERT_TRUE(static_cast<int>(Pack.indicatorsCount) == 111);
    a.exec();
    testing::Mock::VerifyAndClearExpectations(&server.mock);
}

#pragma endregion getIndicatorsQuantityTest

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
