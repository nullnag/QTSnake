#include "ClientNetworkManager.h"
#include "RequestRouter.h"

ClientNetworkManager::ClientNetworkManager(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    requestRouter = new RequestRouter();
    RegistrationHandle* registrationHandle = new RegistrationHandle(this);
    requestRouter->registerHandler("SUCCESS",registrationHandle);
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
    requestRouter->route(data);
}

void ClientNetworkManager::closeConnection()
{

}
