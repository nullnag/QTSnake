#ifndef GAME_H
#define GAME_H

#include "GameField.h"
#include "Snake.h"
#include "Session.h"
#include "GameRules.h"
#include <QPoint>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    Game(Session* session);
    ~Game() override;
    void restartGame();
    void startGame(GameField* gameField, QHash<QString,Snake*> snakes);
    void updateGame() ;
    Snake *getSnake(QString playerName) ;
    void spawnFood() ;
    int getRandomNumber(int min, int max);
private:
    QList<QPoint> foodPositions;
    IGameRules* gameRules;
    Session* session;
    bool isGameStarted = false;
};

#endif // GAME_H
