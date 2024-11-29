#include "RequestRouter.h"

void RequestRouter::registerHandler(const QString &type, IRequestHandler* handler)
{
    handlers[type] = handler;

}

void RequestRouter::route(const QByteArray& data)
{
    QString message = QString::fromUtf8(data).trimmed();
    QString type = message.section(' ', 0, 0).trimmed();
    QString payload = message.section(' ', 1).trimmed();

    if (handlers.contains(type)) {
        handlers[type]->handle(payload);
    } else {
        qDebug() << "Unknown request type:" << type;
    }
}

