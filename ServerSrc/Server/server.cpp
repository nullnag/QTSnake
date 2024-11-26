#include "server.h"


Player::Player(QHostAddress playerAddress, quint16 playerPort) : playerAddress(playerAddress), playerPort(playerPort)
{
}


Server::Server(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    sessionManager = new SessionManager(nullptr);
    requestRouter = new RequestRouter();

    requestRouter->registerHandler("JOIN_SESSION", new JointSessionHandler(this));
    requestRouter->registerHandler("INVITE_PLAYER", new InviteSessionHandler(this));
    requestRouter->registerHandler("CHANGE_DIRECTION", new ChangeDirectionHandler(this));
    requestRouter->registerHandler("CREATE_SESSION", new CreateSessionHandler(this));
    requestRouter->registerHandler("REGISTER_PLAYER", new RegisterPlayerHandler(this));

    socket->bind(12345,QUdpSocket::ShareAddress);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

Server::~Server()
{
    qDeleteAll(players);
    delete socket;
    delete sessionManager;
    delete requestRouter;
}

void Server::sendToPlayer(const QString &playerName, const QByteArray &message)
{
    if (!players.contains(playerName)) {
        qDebug() << "Player not found:" << playerName;
        return;
    }

    Player* player = players[playerName];
    socket->writeDatagram(message, player->playerAddress, player->playerPort);
    qDebug() << "Message sent to" << playerName << ":" << message;
}

void Server::addPlayer(const QString &playerName, const QHostAddress &address, quint16 port)
{
    if (players.contains(playerName)) {
        qDebug() << "Player already exists:" << playerName;
        return;
    }

    players.insert(playerName, new Player(address, port));
    qDebug() << "Player added:" << playerName << "Address:" << address.toString() << "Port:" << port;
}

void Server::removePlayer(const QString &playerName)
{
    if (!players.contains(playerName)) {
        qDebug() << "Player not found:" << playerName;
        return;
    }

    delete players.take(playerName);  // Удаляем игрока и освобождаем память
    qDebug() << "Player removed:" << playerName;
}

SessionManager *Server::getSessionManager()
{
    return sessionManager;
}

QHash<QString, Player *> Server::getPlayers()
{
    return players;
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

void Server::onGameStateUpdate(Session *session, const QByteArray &gameState)
{
    for (const QString& player : session->getPlayers()){
        sendToPlayer(player,gameState);
    }
}

void Server::processIncomingMessage(const QByteArray &data, const QHostAddress &sender, quint16 port)
{
    requestRouter->route(data,sender,port);
}


