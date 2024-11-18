#include "GameWindow.h"
#include <QGraphicsView>


GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{

    gameField = new GameField(this,fieldSize);
    snake = new Snake(gameField,snakeXCoord, snakeYCoord);
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
    if (game) {
        game->keyPressEvent(event);
    }
}
