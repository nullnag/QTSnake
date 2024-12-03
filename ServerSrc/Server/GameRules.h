#ifndef GAMERULES_H
#define GAMERULES_H

#include "Snake.h"
#include <QPoint>
#include "GameField.h"
#include <QHash>

class IGameRules{
public:
    virtual ~IGameRules() = default;
    virtual bool checkCollision(const QString& playerName, const QPoint& newHead) = 0;
    virtual bool isCollisionWithSelf(const QString& playerName,const QPoint& newHead) = 0;
    virtual bool isCollisionWithWall(const QPoint& newHead) = 0;
    virtual bool isCollisionWithFood(const QPoint& newHead,const QPoint& foodPosition) = 0;
    virtual  bool isCollisionWithOtherSnake(QString playerName, const QPoint& newHead) = 0;
};

class GameRules : public IGameRules
{
public:
    GameRules(GameField* gameField, QHash<QString, Snake*> snakes);
    ~GameRules() override;
    bool checkCollision(const QString& playerName,const QPoint& newHead) override;
    bool isCollisionWithSelf(const QString& playerName,const QPoint& newHead) override;
    bool isCollisionWithWall(const QPoint& newHead) override;
    bool isCollisionWithFood(const QPoint& newHead,const QPoint& foodPosition) override;
    bool isCollisionWithOtherSnake(QString playerName, const QPoint& newHead) override;
private:
    GameField* gameField;
    QHash<QString, Snake*> snakes;
};

#endif // GAMERULES_H
