#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGraphicsScene>
#include "Cell.h"
#include <QVector>

class Snake;

class GameField : public QGraphicsScene
{
    Q_OBJECT
public:
    GameField(QObject* parent = nullptr, int sizeField = 16);
    QVector<QVector<Cell*>> getCells();
    int getSize();
    void clear();
    Cell *getCell(int x, int y);
    ~GameField();

private:
    int sizeField;
    QVector<QVector<Cell*>> cells;

};

#endif // GAMEFIELD_H
