#include "GameRules.h"
#include "GameField.h"
#include <QDebug>

GameRules::GameRules(GameField *gameField, QHash<QString, Snake*> snakes) : gameField(gameField), snakes(snakes)
{

}

GameRules::~GameRules()
{
    qDebug() << "~GmeRules()";
}

bool GameRules::checkCollision(const QString& playerName, const QPoint& newHead)
{
    return isCollisionWithSelf(playerName, newHead) ||
           isCollisionWithWall(newHead) ||
           isCollisionWithOtherSnake(playerName, newHead);
}

bool GameRules::isCollisionWithSelf(const QString& playerName, const QPoint& newHead)
{
    const auto& body = (snakes)[playerName]->getBody();
    for (const auto& segment : body) {
        if (segment == newHead) {
            qDebug() << "Игрок" << playerName << "врезался в самого себя.";
            return true;
        }
    }
    return false;
}

bool GameRules::isCollisionWithWall(const QPoint& newHead)
{
    int fieldSize = gameField->getSize();
    return newHead.x() < 0 || newHead.y() < 0 ||
           newHead.x() >= fieldSize || newHead.y() >= fieldSize;
}

bool GameRules::isCollisionWithFood(const QPoint &newHead, const QPoint &foodPosition)
{
    return  newHead == foodPosition;;
}

bool GameRules::isCollisionWithOtherSnake(QString playerName, const QPoint &newHead)
{
    for (auto it = snakes.begin(); it != snakes.end(); ++it) {
        const QString& otherPlayerId = it.key(); // Ключ (например, ID игрока).
        if (otherPlayerId == playerName) continue;
        Snake* snake = it.value();              // Значение (указатель на змейку).
        const auto& body = snake->getBody();
        for (const auto& segment : body) {
            if (segment == newHead) {
                qDebug() << "Игрок" << playerName << "столкнулся с игроком" << otherPlayerId;
                return true;
            }
        }
        qDebug() << "Player ID:" << otherPlayerId << ", Snake Head:" << snake->getHead();
    }
    return false;
}
