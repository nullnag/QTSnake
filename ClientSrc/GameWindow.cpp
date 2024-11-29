#include "GameWindow.h"
#include <QGraphicsView>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent,int fieldSize, IGame* typeOfGame, IInputHandler* inputHandler) :
    fieldSize(fieldSize)
    , QMainWindow(parent)
    , game(typeOfGame)
    , inputHandler(inputHandler)
{
    gameField = new GameField(this,fieldSize);
    gameFieldView = new GameFieldView(gameField,this);

    QGraphicsView* view = new QGraphicsView(gameFieldView, this);
    view->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(view);

    if (game) {
        game->initialize(gameField, this);
    }
}

GameWindow::~GameWindow() {
    delete game;
    delete inputHandler;
    qDebug() << "~GameWindow";
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    inputHandler->handleKeyPress(event,game->getSnake());
    game->startGame();
}
