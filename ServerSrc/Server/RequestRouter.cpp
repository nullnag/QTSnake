#include "RequestRouter.h"
#include <QString>
#include <QDebug>

void RequestRouter::registerHandler(const QString &type, IRequestHandler* handler)
{
    handlers[type] = handler;

}

void RequestRouter::route(const QByteArray &data, const QHostAddress &sender, quint16 port)
{
    QString message = QString::fromUtf8(data);
    QString type = message.section(':',0,0).trimmed();

    if (handlers.contains(type)){
        handlers[type]->handle(message.section(':', 1), sender, port);
    }
    else{
        qDebug() << "Unknown request type";
    }
}
