#include "SinglePlayerGame.h"
#include "SinglePlayerGameOverDialog.h"
#include "SinglePlayerGameWindow.h"
#include <QApplication>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

SinglePlayerGame::SinglePlayerGame(SinglePlayerGameField *SinglePlayerGameField, Snake *snake,SinglePlayerGameWindow* parentWindow) : SinglePlayerGameField(SinglePlayerGameField), snake(snake), parentWindow(parentWindow)
{
    SinglePlayerGameTimer = new QTimer(this);
    connect(SinglePlayerGameTimer, &QTimer::timeout, this, &SinglePlayerGame::updateSinglePlayerGame);
    SinglePlayerGameRules = new SinglePlayerGameRules(SinglePlayerGameField,snake);
    SinglePlayerGame::spawnFood();
}

SinglePlayerGame::~SinglePlayerGame()
{
    qDebug() << "~SinglePlayerGame";
    delete SinglePlayerGameRules;
}

void SinglePlayerGame::restartSinglePlayerGame()
{
    isSinglePlayerGameStarted = false;
    SinglePlayerGameField->clear();
    snake->reset();
    spawnFood();
}

void SinglePlayerGame::endSinglePlayerGame()
{
    QString message;
    if (snake->getBody().size() - 1 == SinglePlayerGameField->getSize() * SinglePlayerGameField->getSize()){
        message = "You won!";
    }
    else{
        message = "You lost!";
    }
    SinglePlayerGameOverDialog dialog(message,nullptr);
    int result = dialog.exec();

    if (result == QDialog::Accepted) {
        restartSinglePlayerGame();
    } else {
        parentWindow->close();
    }
}

void SinglePlayerGame::startSinglePlayerGame()
{
    if (!isSinglePlayerGameStarted) {
        SinglePlayerGameTimer->start(100);
        isSinglePlayerGameStarted = true;
    }
}

void SinglePlayerGame::updateSinglePlayerGame()
{
    snake->move();
    QPoint newHead = snake->calculateNewHead();
    if (SinglePlayerGameRules->checkCollision(newHead)) {
        SinglePlayerGameTimer->stop();
        endSinglePlayerGame();
        return;
    }
    snake->setNewHead(newHead);
    if (SinglePlayerGameRules->isCollisionWithFood(newHead, foodPosition)) {
        qDebug() << "Snake ate the food!";
        SinglePlayerGameField->getCell(foodPosition.x(),foodPosition.y())->setContent(CellContent::Snake);
        spawnFood();

        snake->grow();
    }

}

void SinglePlayerGame::spawnFood()
{
    int fieldSize = SinglePlayerGameField->getSize();
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
    SinglePlayerGameField->getCell(x,y)->setContent(CellContent::Fruit);
    foodPosition = QPoint(x, y);
}

int SinglePlayerGame::getRandomNumber(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}
