#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "GameField.h"
#include "Game.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event);
    GameField* gameField;
    Snake* snake;
    Game* game;
private:
    int fieldSize = 16;
};
#endif // GAMEWINDOW_H
