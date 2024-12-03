#include "Game.h"
#include <QRandomGenerator>
#include <QDebug>


Game::Game(Session* session) : session(session){
}

Game::~Game()
{

}

void Game::restartGame()
{

}

void Game::startGame(GameField* gameField, QHash<QString,Snake*> snakes){
    gameRules = new GameRules(gameField,snakes);
}

void Game::updateGame()
{
    for (const QString& playerName : session->getPlayers()) {
        Snake* snake = session->getSnakeByNickName(playerName);

        // Рассчитываем новое положение головы змейки
        QPoint newHead = snake->calculateNewHead();

        // Проверяем столкновения
        if (gameRules->checkCollision(playerName, newHead)) {
            qDebug() << "Игрок" << playerName << "проиграл!";
            session->deletePlayer(playerName);
            continue;
        }

        // Проверяем, съела ли змейка еду
        for (auto it = foodPositions.begin(); it != foodPositions.end(); ++it) {
            if (gameRules->isCollisionWithFood(newHead, *it)) {
                qDebug() << "Игрок" << playerName << "съел еду!";
                foodPositions.erase(it);
                snake->grow();
                spawnFood();
                break;
            }
        }

        // Обновляем змейку
        snake->move();
    }

    // Проверяем, остался ли один игрок
    if (session->getPlayers().size() <= 0) {
        isGameStarted = false;
        qDebug() << "Игра окончена!";
        session->stopGame();
    }
}

void Game::spawnFood()
{

}

int Game::getRandomNumber(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}
