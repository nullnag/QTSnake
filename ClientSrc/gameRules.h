#ifndef GAMERULES_H
#define GAMERULES_H

#include "Snake.h"

class IGameRules{
public:
    virtual ~IGameRules() = default;
    virtual bool checkCollision(const QPoint& newHead) = 0;
    virtual bool isCollisionWithSelf(const QPoint& newHead) = 0;
    virtual bool isCollisionWithWall(const QPoint& newHead) = 0;
    virtual bool isCollisionWithFood(const QPoint& newHead,const QPoint& foodPosition) = 0;
};

class GameRules : public IGameRules
{
public:
    GameRules(GameField* gameField, Snake* snake);
    ~GameRules() override;
    bool checkCollision(const QPoint& newHead) override;
    bool isCollisionWithSelf(const QPoint& newHead) override;
    bool isCollisionWithWall(const QPoint& newHead) override;
    bool isCollisionWithFood(const QPoint& newHead,const QPoint& foodPosition) override;
private:
    GameField* gameField;
    Snake* snake;
};

#endif // GAMERULES_H
