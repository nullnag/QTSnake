#include "ClientNetworkManager.h"
#include "RequestRouter.h"
#include <QJsonDocument>
#include <QJsonObject>

ClientNetworkManager::ClientNetworkManager(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    requestRouter = new RequestRouter();
    requestRouter->registerHandler("REGISTER_SUCCESS",new RegistrationHandle(this));
    requestRouter->registerHandler("ROOM_CREATED",new CreateRoomHandle(this));
    requestRouter->registerHandler("GAME_STATE", new GameStateHandle(this));
    connect(udpSocket, &QUdpSocket::readyRead,this, &ClientNetworkManager::readPendingDatagrams);
}

ClientNetworkManager::~ClientNetworkManager()
{
    delete udpSocket;
}

bool ClientNetworkManager::connectToServer(const QHostAddress &address, quint16 port, const QString &username)
{
    serverAddress = address;
    serverPort =  port;
    this->username = username;
    if (udpSocket->state() != QAbstractSocket::UnconnectedState) {
        udpSocket->abort();
    }
    if (!udpSocket->bind(QHostAddress::Any, 0)){
        qDebug() << "Failed to bind udp socket";
        return 0;
    }
    QByteArray connectionMessage = QString("REGISTER_PLAYER: %1").arg(username).toUtf8();
    udpSocket->writeDatagram(connectionMessage, serverAddress, serverPort);
    return 1;
}

void ClientNetworkManager::sendMessage(const QByteArray &message)
{
    if (serverAddress.isNull() || serverPort == 0) {
        qWarning() << "Server address or port is not set.";
        return;
    }

    udpSocket->writeDatagram(message, serverAddress, serverPort);
    qDebug() << "Message sent to server:" << message;
}

void ClientNetworkManager::readPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        udpSocket->readDatagram(datagram.data(),datagram.size(),&sender,&senderPort);
        qDebug() << "Message received from" << sender.toString() << ":" << senderPort;
        processIncomingMessage(datagram);
    }
}

void ClientNetworkManager::processIncomingMessage(const QByteArray& data){
    if (data.startsWith('{') && data.endsWith('\n')) {
        // Пытаемся интерпретировать данные как JSON
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject root = doc.object();
            QString type = root.value("type").toString();
            QJsonObject messageData = root.value("data").toObject();

            qDebug() << "JSON Message type:" << type;
            qDebug() << "JSON Message data:" << messageData;

            requestRouter->route(type, QString(QJsonDocument(messageData).toJson(QJsonDocument::Compact)));
            return;
        }
    }

    // Если это не JSON, проверяем, что это текстовая команда
    QString message = QString::fromUtf8(data).trimmed();
    if (!message.isEmpty()) {
        qDebug() << "Text message received:" << message;
        requestRouter->route(message, "");
        return;
    }
}

void ClientNetworkManager::setGameInstance(MultiPlayerGame *game)
{
    this->game = game;
}

MultiPlayerGame *ClientNetworkManager::getGameInstance()
{
    return game;
}

void ClientNetworkManager::closeConnection()
{

}
