#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    sessionManager = new SessionManager();
    requestRouter = new RequestRouter();

    requestRouter->registerHandler("JOIN_SESSION", new JointSessionHandler(sessionManager));
    requestRouter->registerHandler("INVITE_PLAYER", new InviteSessionHandler(sessionManager));
    requestRouter->registerHandler("CHANGE_DIRECTION", new ChangeDirectionHandler(sessionManager));
    requestRouter->registerHandler("CREATE_SESSION", new CreateSessionHandler(sessionManager));

    socket->bind(12345,QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

Server::~Server()
{
    delete socket;
    delete sessionManager;
    delete requestRouter;
}

void Server::readPendingDatagrams()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        socket->readDatagram(data.data(), data.size(), &sender, &senderPort);

        processIncomingMessage(data, sender, senderPort);
    }
}

void Server::processIncomingMessage(const QByteArray &data, const QHostAddress &sender, quint16 port)
{
    requestRouter->route(data,sender,port);
}
