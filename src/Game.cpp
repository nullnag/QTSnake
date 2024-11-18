#include "Game.h"
#include "GameOverDialog.h"
#include <QApplication>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

Game::Game(GameField *gameField, Snake *snake) : gameField(gameField), snake(snake)
{
    gameField->setFocus();
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameRules = new GameRules(gameField,snake);
    spawnFood();
    gameTimer->start(100);
}

Game::~Game()
{
    delete gameRules;
}


void Game::keyPressEvent(QKeyEvent *event)
{
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

void Game::restartGame()
{
    gameField->clear();
    snake->reset();
    spawnFood();
    gameTimer->start(100);
}

void Game::endGame()
{
    QString message;
    if (snake->getBody().size() - 1 == gameField->getSize() * gameField->getSize()){
        message = "You won!";
    }
    else{
        message = "You lost!";
    }
    GameOverDialog dialog(message,nullptr);
    int result = dialog.exec();

    if (result == QDialog::Accepted) {
        restartGame(); // Метод для перезапуска игры
    } else {
        QApplication::quit(); // Завершение приложения
    }
}

void Game::updateGame()
{
    snake->move();
    QPoint newHead = snake->calculateNewHead();
    if (gameRules->checkCollision(newHead)) {
        gameTimer->stop();
        endGame();
        return;
    }
    snake->setNewHead(newHead);
    if (gameRules->isCollisionWithFood(newHead, foodPosition)) {
        qDebug() << "Snake ate the food!";
        gameField->getCell(foodPosition.x(),foodPosition.y())->setContent(CellContent::Snake);
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
    gameField->getCell(x,y)->setContent(CellContent::Fruit);
    foodPosition = QPoint(x, y);
}

int Game::getRandomNumber(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}
