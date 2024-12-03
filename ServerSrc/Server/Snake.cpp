#include "Snake.h"
#include "Cell.h"
#include "GameField.h"
#include <QDebug>
#include <QPoint>

Snake::Snake(GameField *gameField) : gameField(gameField)
{
    direction = Direction::Right;
    pendingDirection = Direction::Right;
}

Snake::~Snake()
{
    qDebug() << "~snake";
}


void Snake::createSnakeBody(const QPoint& spawnPosition)
{
    body.clear();

    // Устанавливаем стартовую позицию головы змеи
    body.push_back(spawnPosition);

    // Обновляем содержимое клетки в игровом поле
    Cell* cell = gameField->getCell(spawnPosition.x(), spawnPosition.y());
    if (cell) {
        cell->setContent(CellContent::Snake);
    }
}

void Snake::move()
{
    if (pendingDirection != direction) {
        direction = pendingDirection;
    }

    // Рассчитываем новое положение головы
    QPoint newHead = calculateNewHead();

    // Удаляем хвост (последнюю клетку тела)
    QPoint tail = body.last();
    Cell* tailCell = gameField->getCell(tail.x(), tail.y());
    if (tailCell) {
        tailCell->setContent(CellContent::Empty);
    }
    body.pop_back();

    // Добавляем новое положение головы
    body.push_front(newHead);
    Cell* headCell = gameField->getCell(newHead.x(), newHead.y());
    if (headCell) {
        headCell->setContent(CellContent::Snake);
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

void Snake::reset()
{
    body.clear();
    direction = Direction::Right;
    pendingDirection = Direction::Right;
}

QPoint Snake::getHead()
{
    return body.first();
}

QList<QPoint> Snake::getBody()
{
    return body;
}



