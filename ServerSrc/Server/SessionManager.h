#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Session.h"
#include <QHash>

class SessionManager
{
public:
    SessionManager();
    void createSession(const QString& leaderName,const int countOfPlayers, const int fieldSize);
    void deleteSession();
    void addPlayerToSession(const QString& leaderName,const QString& joiningPlayer);
    Session* getSessionByPlayer(const QString& nickname);
private:
    QHash<QString,Session*> sessions;
};

#endif // SESSIONMANAGER_H
