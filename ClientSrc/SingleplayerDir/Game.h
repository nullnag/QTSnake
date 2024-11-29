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
    virtual void initialize(GameField* gameField, GameWindow* parentWindow) = 0;
    virtual void restartGame() = 0;
    virtual void endGame() = 0;
    virtual void startGame() = 0;
    virtual Snake* getSnake() = 0;
    virtual void updateGame() = 0;
    virtual void spawnFood() = 0;
};

class Game : public QObject, public IGame
{
    Q_OBJECT
public:
    Game() = default;
    ~Game() override;
    void restartGame() override;
    void endGame() override;
    void initialize(GameField* gameField, GameWindow* parentWindow) override;
    void startGame() override;
    void updateGame() override;
    Snake *getSnake() override;
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
