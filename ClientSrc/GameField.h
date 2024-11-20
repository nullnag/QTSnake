#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "Cell.h"
#include <QVector>

class GameField : public QObject
{
    Q_OBJECT
public:
    GameField(QObject* parent = nullptr, int sizeField = 16);
    int getSize();
    void clear();
    Cell *getCell(int x, int y);
    ~GameField();
signals:
    void fieldCleared();
    void cellUpdated(int x, int y, CellContent content);
private:
    int size;
    QVector<QVector<Cell*>> cells;

};

#endif // GAMEFIELD_H
