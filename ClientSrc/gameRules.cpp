#include "gameRules.h"
#include <QDebug>

GameRules::GameRules(GameField *gameField, Snake *snake) : gameField(gameField), snake(snake)
{

}

GameRules::~GameRules()
{

}

bool GameRules::checkCollision(const QPoint& newHead)
{
    return isCollisionWithSelf(newHead) || isCollisionWithWall(newHead);
}

bool GameRules::isCollisionWithSelf(const QPoint& newHead)
{
    const auto& body = snake->getBody();
    for (const auto& segment : body) {
        if (segment == newHead) {
            qDebug() << "Змейка ударилась в себя";
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
