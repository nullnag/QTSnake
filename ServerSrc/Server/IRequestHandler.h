#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include <QByteArray>
#include <QHostAddress>

class Server;

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual void handle(const QString& data, const QHostAddress& sender, quint16 port) = 0;
};

class CreateSessionHandler : public IRequestHandler {
public:
    explicit CreateSessionHandler(Server* server);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    Server* server;
};

class JointSessionHandler : public IRequestHandler {
public:
    explicit JointSessionHandler(Server* Server);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    Server* server;
};

class InviteSessionHandler : public IRequestHandler{
public:
    explicit InviteSessionHandler(Server* Server);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    Server* server;
};

class ChangeDirectionHandler : public IRequestHandler{
public:
    explicit ChangeDirectionHandler(Server* Server);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    Server* server;
};

class RegisterPlayerHandler : public IRequestHandler {
public:
    explicit RegisterPlayerHandler(Server* Server);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    Server* server;
};

#endif // IREQUESTHANDLER_H
