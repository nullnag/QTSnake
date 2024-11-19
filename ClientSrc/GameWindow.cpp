#include "GameWindow.h"
#include <QGraphicsView>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent,int fieldSize) :
    fieldSize(fieldSize)
    , QMainWindow(parent)
{

    gameField = new GameField(this,fieldSize);
    snake = new Snake(gameField);
    game = new Game(gameField,snake,this);
    QGraphicsView* view = new QGraphicsView(gameField, this);
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
    QMainWindow::keyPressEvent(event);
    if (game) {
        game->keyPressEvent(event);
    }
}
