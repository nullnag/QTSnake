#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "Snake.h"
#include "GameRules.h"
#include <QWidget>

class GameWindow;


class IGame {
public:
    virtual ~IGame() = default;
    virtual void restartGame() = 0;
    virtual void endGame() = 0;
    virtual void startGame() = 0;
    virtual void updateGame() = 0;
    virtual void spawnFood() = 0;
};

class Game : public QObject, public IGame
{
    Q_OBJECT
public:
    Game(GameField* gameField = nullptr, Snake* snake = nullptr,GameWindow* parentWindow = nullptr);
    ~Game() override;
    void restartGame() override;
    void endGame() override;
    void startGame() override;
    void updateGame() override;
    void spawnFood() override;
    int getRandomNumber(int min, int max);
private:
    QPoint foodPosition;
    IGameRules* gameRules;
    QTimer* gameTimer;
    GameField* gameField;
    Snake* snake;
    GameWindow* parentWindow;
    bool isGameStarted = false;
};

#endif // GAME_H
