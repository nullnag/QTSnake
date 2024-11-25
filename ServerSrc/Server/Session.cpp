#include "Session.h"

Session::Session(QObject* parent,int countOfPlayers, int fieldSize) : countOfPlayers(countOfPlayers), fieldSize(fieldSize), QObject(parent)
{
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer,&QTimer::timeout,this,&Session::updateGameState);
}

Session::~Session()
{
    for (auto snake : snakes) {
        delete snake;
    }
}

void Session::startGame()
{
    if (snakes.size() == countOfPlayers){
        gameUpdateTimer->start();
    }
}

void Session::addPlayer(const QString& nickname)
{
    snakes[nickname] = new Snake();
}

void Session::deletePlayer(const QString& nickname)
{
    snakes.remove(nickname);
}

bool Session::hasPlayer(const QString &nickname)
{
    return snakes.contains(nickname);
}

void Session::updateGameState()
{
    QByteArray gameState = serializeGameState();
}

Snake *Session::getSnakeByNickName(const QString &nickname)
{
    return snakes[nickname];
}

QByteArray Session::serializeGameState() const
{

}
