#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Session.h"
#include <QByteArray>
#include <QHash>

class SessionManager : public QObject
{
    Q_OBJECT
public:
    SessionManager(QObject* parent = nullptr);
    void createSession(const QString& leaderName,const int countOfPlayers, const int fieldSize);
    void deleteSession();
    void addPlayerToSession(const QString& leaderName,const QString& joiningPlayer);
    Session* getSessionByPlayer(const QString& nickname);
signals:
    void updateGameState(Session* session, const QByteArray& gameState);
private:
    QHash<QString,Session*> sessions;
};

#endif // SESSIONMANAGER_H
