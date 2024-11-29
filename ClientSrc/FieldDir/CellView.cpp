#include "CellView.h"
#include <QBrush>


const QMap<CellContent,QBrush> CellView::brushMap = {
    {CellContent::Empty, QBrush(Qt::white)},
    {CellContent::Fruit, QBrush(Qt::red)},
    {CellContent::Snake, QBrush(Qt::green)},
};



CellView::CellView(Cell *model, QGraphicsItem *parent) : QGraphicsRectItem(parent), model(model)
{
    setRect(model->getX() * 50, model->getY() * 50, 50, 50);
    connect(model, &Cell::contentChanged, this, &CellView::updateContent);
}

void CellView::updateContent(int x, int y, CellContent content)
{
    auto it = brushMap.find(content);
    if (it != brushMap.end()){
        setBrush(brushMap[content]);
    }
}
