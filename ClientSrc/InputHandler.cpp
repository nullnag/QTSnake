#include "InputHandler.h"

void DefaultInputHandler::handleKeyPress(QKeyEvent *event, Snake *snake)
{
    switch (event->key()) {
    case Qt::Key_W:
        if (snake->getDirection() != Direction::Down) snake->changeDirection(Direction::Up);
        break;
    case Qt::Key_S:
        if (snake->getDirection() != Direction::Up) snake->changeDirection(Direction::Down);
        break;
    case Qt::Key_A:
        if (snake->getDirection() != Direction::Right) snake->changeDirection(Direction::Left);
        break;
    case Qt::Key_D:
        if (snake->getDirection() != Direction::Left) snake->changeDirection(Direction::Right);
        break;
    }
}


void MultiPlayerInputHandler::handleKeyPress(QKeyEvent *event, Snake *snake)
{
    qDebug() << "Multiplayer input";
}
