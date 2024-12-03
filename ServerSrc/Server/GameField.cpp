#include "GameField.h"
#include "Cell.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

GameField::GameField(QObject* parent, int size) : QObject(parent), size(size) {
    cells.resize(size);
    cells.resize(size);
    for (int x = 0; x < size; ++x) {
        cells[x].resize(size);
        for (int y = 0; y < size; ++y) {
            cells[x][y] = new Cell(this, x, y);
        }
    }
}

int GameField::getSize()
{
    return size;
}

void GameField::clear()
{
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell->setContent(CellContent::Empty);
        }
    }
    emit fieldCleared();
}

Cell *GameField::getCell(int x, int y)
{
    if (x > size || y > size){
        return nullptr;
    }
    return cells[x][y];
}

GameField::~GameField()
{
    qDebug() << "~gameField";
    for (auto& row : cells) {
        qDeleteAll(row);
    }
}
