#ifndef REQUESTROUTER_H
#define REQUESTROUTER_H

#include "IRequestHandler.h"
#include <QHash>

class RequestRouter
{
public:
    RequestRouter() = default;
    void registerHandler(const QString& type, IRequestHandler* handler);
    void route(const QByteArray& data);
private:
    QHash<QString, IRequestHandler*> handlers;
};

#endif // REQUESTROUTER_H
