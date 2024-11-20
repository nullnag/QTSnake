#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include "GameField.h"
#include "InputHandler.h"
#include "GameFieldView.h"
#include "Game.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr,int fieldSize = 16);
    ~GameWindow();
    void keyPressEvent(QKeyEvent *event);
    GameField* gameField;
    GameFieldView* gameFieldView;
    Snake* snake;
    IInputHandler* inputHandler;
    Game* game;
private:
    int fieldSize = 16;
};
#endif // GAMEWINDOW_H
