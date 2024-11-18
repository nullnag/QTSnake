#include "GameField.h"
#include "Cell.h"
#include <QTimer>
#include <QObject>
#include <QKeyEvent>

GameField::GameField(QObject* parent, int sizeField) : QGraphicsScene(parent), sizeField(sizeField) {
    cells.resize(sizeField);
    for (int x = 0; x < sizeField; x++){
        cells[x].resize(sizeField);
        for (int y = 0; y < sizeField; y++){
            Cell* cell = new Cell(nullptr, x * 50 , y * 50);
            addItem(cell); // Добавляем клетку на сцену
            cells[x][y] = cell;
        }
    }
}

QVector<QVector<Cell*>> GameField::getCells()
{
    return cells;
}


int GameField::getSize()
{
    return sizeField;
}

void GameField::clear()
{
    for (int x = 0; x < sizeField; x++){
        cells[x].resize(sizeField);
        for (int y = 0; y < sizeField; y++){
            cells[x][y]->setContent(CellContent::Empty);
        }
    }
}

Cell *GameField::getCell(int x, int y)
{
    return cells[x][y];
}

GameField::~GameField()
{
    for (auto i : cells){
        for (auto j : i){
            delete j;
        }
    }
}
