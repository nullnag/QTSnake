#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include <QByteArray>
#include "SessionManager.h"
#include <QHostAddress>

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual void handle(const QString& data, const QHostAddress& sender, quint16 port) = 0;
};

class CreateSessionHandler : public IRequestHandler {
public:
    explicit CreateSessionHandler(SessionManager* sessionManager);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    SessionManager* sessionManager;
};

class JointSessionHandler : public IRequestHandler {
public:
    explicit JointSessionHandler(SessionManager* sessionManager);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    SessionManager* sessionManager;
};

class InviteSessionHandler : public IRequestHandler{
public:
    explicit InviteSessionHandler(SessionManager* sessionManager);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    SessionManager* sessionManager;
};

class ChangeDirectionHandler : public IRequestHandler{
public:
    explicit ChangeDirectionHandler(SessionManager* sessionManager);
    void handle(const QString& data, const QHostAddress& sender, quint16 port) override;
private:
    SessionManager* sessionManager;
};


#endif // IREQUESTHANDLER_H
