#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "IRequestHandler.h"

class RequestRouter
{
public:
    RequestRouter() = default;
    void registerHandler(const QString& type, IRequestHandler* handler);
    void route(const QByteArray& data, const QHostAddress& sender, quint16 port);
private:
    QHash<QString, IRequestHandler*> handlers;
};

#endif // REQUESTROUTER_H
