#ifndef SERVER_H
#define SERVER_H


#include <QUdpSocket>
#include <QObject>
#include "SessionManager.h"
#include "RequestRouter.h"

struct Player{
    Player(QHostAddress playerAddress, quint16 playerPort);
    QHostAddress playerAddress;
    quint16 playerPort;
};

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
    ~Server();
    void sendToPlayer(const QString& playerName, const QByteArray& message);
    void addPlayer(const QString& playerName, const QHostAddress& address, quint16 port);
    void removePlayer(const QString& playerName);
    SessionManager *getSessionManager();
    QHash<QString,Player*> getPlayers();
public slots:
    void readPendingDatagrams();
    void onGameStateUpdate(Session* session, const QByteArray& gameState);

private:
    void processIncomingMessage(const QByteArray& data, const QHostAddress& sender, quint16 port);
    SessionManager* sessionManager;
    RequestRouter* requestRouter;
    QUdpSocket* socket;
    QHash<QString,Player*> players;
};

#endif // SERVER_H
