#include "IRequestHandler.h"


CreateSessionHandler::CreateSessionHandler(SessionManager *sessionManager) : sessionManager(sessionManager)
{
    return;
}

void CreateSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    return;
}

JointSessionHandler::JointSessionHandler(SessionManager *sessionManager) : sessionManager(sessionManager)
{
    return;
}

void JointSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    return;
}

InviteSessionHandler::InviteSessionHandler(SessionManager *sessionManager) : sessionManager(sessionManager)
{
    return;
}

void InviteSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    return;
}

ChangeDirectionHandler::ChangeDirectionHandler(SessionManager *sessionManager) : sessionManager(sessionManager)
{
    return;
}

void ChangeDirectionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    return;
}

