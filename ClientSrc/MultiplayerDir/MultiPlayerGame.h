#ifndef MULTIPLAYERGAME_H
#define MULTIPLAYERGAME_H

#include "Game.h"

class MultiPlayerGame : public QObject, public IGame {
    Q_OBJECT
public:
    MultiPlayerGame() = default;
    ~MultiPlayerGame() override;
    void restartGame() override;
    void endGame() override;
    void initialize(GameField* gameField, GameWindow* parentWindow) override;
    void startGame() override;
    Snake *getSnake() override;
    void updateGame() override;
    void spawnFood() override;
private:
    QVector<QPoint> foodPositions;
    GameField* gameField;
    GameWindow* parentWindow;
    bool isGameStarted = false;
};

#endif // MULTIPLAYERGAME_H
