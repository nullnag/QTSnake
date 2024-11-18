#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include "GameField.h"

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

class Snake : public QObject
{
    Q_OBJECT
public:
    Snake(GameField* gameField, int x, int y);

    void move();
    void grow();
    void changeDirection(Direction dir);
    void reset();
    void setNewHead(QPoint head);
    Direction getDirection();
    QPoint calculateNewHead();
    QPoint getHead();
    QList<QPoint> getBody();
private:
    int startX;
    int startY;
    GameField* gameField;
    QList<QPoint> body;
    Direction direction;
    Direction pendingDirection;
};

#endif // SNAKE_H
