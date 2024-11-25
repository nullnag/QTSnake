#include "SessionManager.h"

SessionManager::SessionManager() {}

void SessionManager::createSession(const QString& leaderName,const int countOfPlayers,const int fieldSize)
{
    sessions[leaderName] = new Session(nullptr,countOfPlayers,fieldSize);
    sessions[leaderName]->addPlayer(leaderName);
}

void SessionManager::addPlayerToSession(const QString& leaderName,const QString& joiningPlayer)
{
    sessions[leaderName]->addPlayer(joiningPlayer);
}

Session *SessionManager::getSessionByPlayer(const QString& nickname)
{
    for (Session* session : sessions){
        if (session->hasPlayer(nickname)){
            return session;
        }
    }
    return nullptr;
}


