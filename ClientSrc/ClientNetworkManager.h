#ifndef CLIENTNETWORKMANAGER_H
#define CLIENTNETWORKMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class RequestRouter;

class ClientNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientNetworkManager(QObject* parent = nullptr);
    ~ClientNetworkManager();

    bool connectToServer(const QHostAddress& serverAddress, quint16 serverPort, const QString& username);
    void sendMessage(const QByteArray& message);
    void processIncomingMessage(const QByteArray& data);
    void closeConnection();
signals:
    void messageReceived(const QByteArray& message, const QHostAddress& sender, quint16 senderPort);
    void openMultiPlayerMenu();
private slots:
    void readPendingDatagrams();
private:
    RequestRouter* requestRouter;
    QUdpSocket* udpSocket;
    QHostAddress serverAddress;
    quint16 serverPort;
    QString username;
 };

#endif // CLIENTNETWORKMANAGER_H
