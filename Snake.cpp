#include "Snake.h"
#include "Cell.h"
#include "GameField.h"
#include <QKeyEvent>

Snake::Snake(GameField *gameField, int x, int y) : gameField(gameField)
{
    direction = Direction::Right;
    pendingDirection = Direction::Right;
    body.append(QPoint(x, y));
    body.append(QPoint(x - 1, y));
    body.append(QPoint(x - 2, y));
    for (const auto& segment : body) {
        gameField->getCell(segment.x(),segment.y())->setContent(CellContent::Snake);
    }

}

void Snake::move()
{
    if (pendingDirection != direction) {
        direction = pendingDirection;
    }
    QPoint tail = body.last();
    Cell* tailCell = gameField->getCell(tail.x(),tail.y());
    if (tailCell) {
        tailCell->setContent(CellContent::Empty);
    }
    for (int i = body.size() - 1; i > 0; --i) {
        body[i] = body[i - 1];
    }

}

QPoint Snake::calculateNewHead()
{
    QPoint head = getHead();
    switch (direction) {
    case Direction::Up:
        head.setY(head.y() - 1);
        break;
    case Direction::Down:
        head.setY(head.y() + 1);
        break;
    case Direction::Left:
        head.setX(head.x() - 1);
        break;
    case Direction::Right:
        head.setX(head.x() + 1);
        break;
    }
    return head;
}

void Snake::setNewHead(QPoint head)
{
    body[0] = head;
    Cell* headCell = gameField->getCell(head.x(),head.y());
    if (headCell) {
        headCell->setContent(CellContent::Snake);
    }
}

Direction Snake::getDirection()
{
    return direction;
}


void Snake::grow()
{
    body.push_back(body.last());
}

void Snake::changeDirection(Direction dir)
{
    if ((direction == Direction::Up && dir != Direction::Down) ||
        (direction == Direction::Down && dir != Direction::Up) ||
        (direction == Direction::Left && dir != Direction::Right) ||
        (direction == Direction::Right && dir != Direction::Left)) {
        pendingDirection = dir;
    }
}

QPoint Snake::getHead()
{
    return body.first();
}

QList<QPoint> Snake::getBody()
{
    return body;
}


