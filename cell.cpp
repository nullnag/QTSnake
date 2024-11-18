#include "cell.h"
#include <QBrush>

const QMap<CellContent,QBrush> Cell::brushMap = {
    {CellContent::Empty, QBrush(Qt::white)},
    {CellContent::Fruit, QBrush(Qt::red)},
    {CellContent::Snake, QBrush(Qt::green)},
};


Cell::Cell(QGraphicsItem* parent , int x, int y)  : QGraphicsRectItem(parent), m_content(CellContent::Empty), mX(x), mY(y) {
    setRect(x,y,50,50);
    updateBrush();
}
// ааа
void Cell::setContent(CellContent content)
{
    m_content = content;
    updateBrush();
}

CellContent Cell::getContent() const
{
    return m_content;
}

bool Cell::isEmpty()
{
    return m_content == CellContent::Empty;
}

QPoint Cell::getPosition() const
{
    return QPoint(mX,mY);
}

void Cell::removeContent()
{
    setContent(CellContent::Empty);
}

void Cell::updateBrush()
{
    auto it = brushMap.find(m_content);
    if (it != brushMap.end()){
        setBrush(brushMap[m_content]);
    }
}

