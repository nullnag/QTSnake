#include "Game.h"
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QTimer>

Game::Game(GameField *gameField, Snake *snake) : gameField(gameField), snake(snake)
{
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameTimer->start(50);
    gameRules = new GameRules(gameField,snake);
    spawnFood();
}

Game::~Game()
{
    delete gameRules;
}


void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;
    switch (event->key()) {
    case Qt::Key_W:
        if (snake->getDirection() != Direction::Down) {
            snake->changeDirection(Direction::Up);
        }
        break;
    case Qt::Key_S:
        if (snake->getDirection() != Direction::Up) {
            snake->changeDirection(Direction::Down);
        }
        break;
    case Qt::Key_A:
        if (snake->getDirection() != Direction::Right) {
            snake->changeDirection(Direction::Left);
        }
        break;
    case Qt::Key_D:
        if (snake->getDirection() != Direction::Left) {
            snake->changeDirection(Direction::Right);
        }
        break;
    }
}

void Game::endGame()
{
    if (snake->getBody().size() - 1 == gameField->getSize() * gameField->getSize()){
        qDebug() << "Вы выйграли";
        return;
    }
    else{
        qDebug() << "Вы проиграли";
        return;
    }
}

void Game::updateGame()
{
    snake->move();
    QPoint newHead = snake->calculateNewHead();
    if (gameRules->checkCollision(newHead)) {
        endGame();
        gameTimer->stop();
        return;
    }
    snake->setNewHead();
    if (gameRules->isCollisionWithFood(newHead, foodPosition)) {
        qDebug() << "Snake ate the food!";
        gameField->getCells()[foodPosition.x()][foodPosition.y()]->setContent(CellContent::Snake);
        spawnFood();

        snake->grow();
    }

}

void Game::spawnFood()
{
    int fieldSize = gameField->getSize();
    if (snake->getBody().size() == fieldSize * fieldSize) {
        qDebug() << "No space left for food!";
        return; // Поле полностью занято
    }
    int x, y;
    bool valid = false;
    while (!valid) {
        x = getRandomNumber(0, fieldSize - 1);
        y = getRandomNumber(0, fieldSize - 1);
        bool occupiedBySnake = false;
        for (const auto& segment : snake->getBody()) {
            if (segment == QPoint(x, y)) {
                occupiedBySnake = true;
                break;
            }
        }

        if (!occupiedBySnake) {
            valid = true; // Нашли подходящую клетку
        }
    }
    qDebug() << "Food spawned at:" << x << y;
    gameField->getCells()[x][y]->setContent(CellContent::Fruit);
    foodPosition = QPoint(x, y);
}

int Game::getRandomNumber(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}
