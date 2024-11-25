#ifndef SERVER_H
#define SERVER_H


#include <QUdpSocket>
#include <QObject>
#include "SessionManager.h"
#include "RequestRouter.h"

class Server : QObject
{
    Q_OBJECT
public:
    Server(QObject *parent);
    ~Server();
private slots:
    void readPendingDatagrams();
private:
    void processIncomingMessage(const QByteArray& data, const QHostAddress& sender, quint16 port);
    SessionManager* sessionManager;
    RequestRouter* requestRouter;
    QUdpSocket* socket;
};

#endif // SERVER_H
