#include "Session.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "Game.h"

Session::Session(QObject* parent,int countOfPlayers, int fieldSize) : countOfPlayers(countOfPlayers), fieldSize(fieldSize), QObject(parent)
{
    gameUpdateTimer = new QTimer(this);
    connect(gameUpdateTimer,&QTimer::timeout,this,&Session::onGameTick);
    gameField = new GameField(this,fieldSize);
    game = new Game(this);
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
        game->startGame(gameField,snakes);
        gameUpdateTimer->start(500);

    }
}

void Session::stopGame()
{
    gameUpdateTimer->stop();
}

void Session::addPlayer(const QString& nickname)
{
    if (snakes.size() < countOfPlayers){
        QPoint spawnPosition = getUniqueSpawnPosition();
        snakes[nickname] = new Snake(gameField);
        QPoint test = QPoint(5,5);
        snakes[nickname]->createSnakeBody(test);
    }
    startGame();
}

void Session::deletePlayer(const QString& nickname)
{
    snakes.remove(nickname);
}

GameField *Session::getGameField()
{
    return gameField;
}

bool Session::hasPlayer(const QString &nickname)
{
    return snakes.contains(nickname);
}

QList<QString> Session::getPlayers() const
{
    return snakes.keys();
}

Snake *Session::getSnakeByNickName(const QString &nickname) const
{
    return snakes[nickname];
}

QHash<QString, Snake *> Session::getSnakes()
{
    return snakes;
}

QPoint Session::getUniqueSpawnPosition()
{
    int fieldSize = gameField->getSize();
    for (int y = 0; y < fieldSize; ++y) {
        for (int x = 0; x < fieldSize; ++x) {
            QPoint potentialPosition(x, y);
            if (isPositionFree(potentialPosition)) {
                return potentialPosition;
            }
        }
    }

    return QPoint(0, 0);
}

bool Session::isPositionFree(const QPoint &position)
{
    for (const auto& snake : snakes) {
        if (snake->getHead() == position) {
            return false; // Позиция занята другой змеёй
        }
    }
    return gameField->getCell(position.x(), position.y())->isEmpty();
}

QByteArray Session::serializeGameState() const
{
    QJsonObject gameStateJson;
    QJsonObject snakesJson;
    for (const QString& playerName : getPlayers()) {
        Snake* snake = getSnakeByNickName(playerName);
        QJsonArray bodyArray;
        for (const QPoint& segment : snake->getBody()) {
            QJsonObject segmentJson;
            segmentJson["x"] = segment.x();
            segmentJson["y"] = segment.y();
            qDebug() << "snake X:" << segment.x();
            qDebug() << "snake Y:" << segment.y();

            bodyArray.append(segmentJson);
        }
        snakesJson[playerName] = bodyArray;
    }
    gameStateJson["snakes"] = snakesJson;

    // Преобразуем JSON в QByteArray
    QJsonDocument doc(gameStateJson);
    return doc.toJson();
}

void Session::onGameTick()
{
    game->updateGame();
    emit updateGameState();
}
