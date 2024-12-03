#include "RequestRouter.h"

void RequestRouter::registerHandler(const QString &type, IRequestHandler* handler)
{
    handlers[type] = handler;

}

void RequestRouter::route(const QString& type, const QString& content)
{
    if (handlers.contains(type)) {
        handlers[type]->handle(content);
    } else {
        qWarning() << "No handler registered for message type:" << type;
    }
}

