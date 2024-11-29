#include "Game.h"
#include "GameOverDialog.h"
#include "GameWindow.h"
#include <QApplication>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

Game::~Game()
{
    qDebug() << "~Game";
    delete gameRules;
    delete snake;
}

void Game::restartGame()
{
    isGameStarted = false;
    gameField->clear();
    snake->reset();
    spawnFood();
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
        restartGame();
    } else {
        parentWindow->close();
    }
}

void Game::initialize(GameField *gameField, GameWindow* parentWindow)
{
    this->gameField = gameField;
    this->parentWindow = parentWindow;
    snake = new Snake(gameField);
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameRules = new GameRules(gameField,snake);
    Game::spawnFood();
}

void Game::startGame()
{
    if (!isGameStarted) {
        gameTimer->start(100);
        isGameStarted = true;
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

Snake *Game::getSnake()
{
    return snake;
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
            valid = true;
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
