#include "SessionManager.h"

SessionManager::SessionManager(QObject* parent) : QObject(parent) {
}

void SessionManager::createSession(const QString& leaderName,const int countOfPlayers,const int fieldSize)
{
    Session* newSession = new Session(nullptr,countOfPlayers,fieldSize);
    sessions[leaderName] = newSession;
    sessions[leaderName]->addPlayer(leaderName);
    connect(newSession, &Session::updateGameState, this, [this, newSession]() {
        QByteArray gameState = newSession->serializeGameState();
        emit updateGameState(newSession, gameState);
    });
}

void SessionManager::addPlayerToSession(const QString& leaderName,const QString& joiningPlayer)
{
    sessions[leaderName]->addPlayer(joiningPlayer);
}

Session *SessionManager::getSessionByPlayer(const QString& nickname)
{
    for (Session* session : qAsConst(sessions)){
        if (session->hasPlayer(nickname)){
            return session;
        }
    }
    return nullptr;
}


