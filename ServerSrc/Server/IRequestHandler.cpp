#include "IRequestHandler.h"
#include "Server.h"

CreateSessionHandler::CreateSessionHandler(Server *server) : server(server)
{

}

void CreateSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    // Формат команды: "CREATE_SESSION:<leaderName>:<countOfPlayers>:<fieldSize>"
    QStringList parts = data.split(':');
    if (parts.size() < 4) {
        qDebug() << "Invalid CREATE_SESSION format:" << data;
        // Ответ об ошибке
        return;
    }

    QString leaderName = parts[1];              // Извлечение имени лидера
    bool countOk = false;
    int countOfPlayers = parts[2].toInt(&countOk); // Извлечение количества игроков
    if (!countOk) {
        qDebug() << "Invalid countOfPlayers value:" << parts[2];
        // Ответ об ошибке
        return;
    }

    bool sizeOk = false;
    int fieldSize = parts[3].toInt(&sizeOk);    // Извлечение размера поля
    if (!sizeOk) {
        qDebug() << "Invalid fieldSize value:" << parts[3];
        // Ответ об ошибке
        return;
    }

    // Создание сессии через Server
    server->getSessionManager()->createSession(leaderName, countOfPlayers, fieldSize);
}


JointSessionHandler::JointSessionHandler(Server *server) : server(server)
{

}

void JointSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{

}

InviteSessionHandler::InviteSessionHandler(Server *server) : server(server)
{

}

void InviteSessionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    QStringList parts = data.split(' ');
    if (parts.size() < 3) {
        qDebug() << "Invalid INVITE_PLAYER command format.";
        return;
    }

    QString inviterName = parts[1];
    QString inviteeName = parts[2];

    if (!server->getPlayers().contains(inviteeName)) {
        qDebug() << "Invitee not found:" << inviteeName;
        return;
    }

    QByteArray inviteMessage = QString("INVITE from %1").arg(inviterName).toUtf8();
    server->sendToPlayer(inviteeName, inviteMessage);

    QByteArray response = "SUCCESS Invitation sent";
    server->sendToPlayer(inviterName, response);
}

ChangeDirectionHandler::ChangeDirectionHandler(Server *server) : server(server)
{

}

void ChangeDirectionHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{

}


RegisterPlayerHandler::RegisterPlayerHandler(Server *server) : server(server)
{

}

void RegisterPlayerHandler::handle(const QString &data, const QHostAddress &sender, quint16 port)
{
    QStringList parts = data.split(' ');
    if (parts.size() < 2) {
        qDebug() << "Invalid REGISTER_PLAYER command format.";
        return;
    }

    QString playerName = parts[1];
    if (server->getPlayers().contains(playerName)) {
        QByteArray response = "ERROR Player already registered";
        server->sendToPlayer(playerName, response);
        return;
    }

    server->addPlayer(playerName, sender, port);
    QByteArray response = "SUCCESS Player registered";
    server->sendToPlayer(playerName, response);
}
