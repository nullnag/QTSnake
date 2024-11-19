#ifndef GAMERULES_H
#define GAMERULES_H

#include "Snake.h"

class GameRules
{
public:
    GameRules(GameField* gameField, Snake* snake);
    bool checkCollision(const QPoint& newHead);
    bool isCollisionWithSelf(const QPoint& newHead);
    bool isCollisionWithWall(const QPoint& newHead);
    bool isCollisionWithFood(const QPoint& newHead,const QPoint& foodPosition);
private:
    GameField* gameField;
    Snake* snake;
};

#endif // GAMERULES_H
