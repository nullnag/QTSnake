#include "GameWindow.h"
#include <QGraphicsView>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent,int fieldSize) :
    fieldSize(fieldSize)
    , QMainWindow(parent)
{


    gameField = new GameField(this,fieldSize);
    gameFieldView = new GameFieldView(gameField,this);
    snake = new Snake(gameField);
    inputHandler = new DefaultInputHandler();
    game = new Game(gameField,snake,this);


    QGraphicsView* view = new QGraphicsView(gameFieldView, this);
    view->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(view);

}

GameWindow::~GameWindow() {
    delete game;
    delete snake;
    qDebug() << "~GameWindow";
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    inputHandler->handleKeyPress(event,snake);
    game->startGame();
}
