#ifndef CELLVIEW_H
#define CELLVIEW_H

#include <QObject>
#include <QGraphicsRectItem>

#include "Cell.h"



class CellView : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit CellView(Cell* model,QGraphicsItem* parent = nullptr);
public slots:
    void updateContent(int x, int y, CellContent content);
private:
    Cell* model;
    static const QMap<CellContent,QBrush> brushMap;
};

#endif // CELLVIEW_H
