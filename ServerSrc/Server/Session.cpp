#include "Session.h"

Session::Session(QObject* parent,int countOfPlayers, int fieldSize) : countOfPlayers(countOfPlayers), fieldSize(fieldSize), QObject(parent)
{
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer,&QTimer::timeout,this,&Session::onGameTick);
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
    if (snakes.size() < countOfPlayers){
        snakes[nickname] = new Snake();
    }
    startGame();
}

void Session::deletePlayer(const QString& nickname)
{
    snakes.remove(nickname);
}

bool Session::hasPlayer(const QString &nickname)
{
    return snakes.contains(nickname);
}

QList<QString> Session::getPlayers()
{
    return snakes.keys();
}

Snake *Session::getSnakeByNickName(const QString &nickname)
{
    return snakes[nickname];
}

QByteArray Session::serializeGameState() const
{

}

void Session::onGameTick()
{
    emit updateGameState();
}
