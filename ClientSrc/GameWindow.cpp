#include "GameWindow.h"
#include <QGraphicsView>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{

    gameField = new GameField(this,fieldSize);
    snake = new Snake(gameField);
    game = new Game(gameField,snake);
    QGraphicsView* view = new QGraphicsView(gameField, this);
    view->setFocusPolicy(Qt::StrongFocus);
    setCentralWidget(view);

}

GameWindow::~GameWindow() {
    delete gameField;
    delete snake;
    delete game;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);
    if (game) {
        game->keyPressEvent(event);
    }
}
