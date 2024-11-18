#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "Snake.h"
#include "GameRules.h"
#include <QWidget>

class GameWindow;

class Game : public QObject
{
    Q_OBJECT
public:
    Game(GameField* gameField = nullptr, Snake* snake = nullptr);
    ~Game();
    void keyPressEvent(QKeyEvent *event);
    void endGame();
    void updateGame();
    void spawnFood();
    int getRandomNumber(int min, int max);
private:
    QPoint foodPosition;
    GameRules* gameRules;
    QTimer* gameTimer;
    GameField* gameField;
    Snake* snake;
};

#endif // GAME_H
