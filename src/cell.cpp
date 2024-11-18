#include "cell.h"
#include <QBrush>

Cell::Cell(QGraphicsItem* parent , int x, int y)  : QGraphicsRectItem(parent), m_content(CellContent::Empty), mX(x), mY(y) {
    setRect(x,y,50,50);
    updateBrush();
}

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
    switch (m_content)
    {
    case CellContent::Empty:
        setBrush(QBrush(Qt::white));
        break;
    case CellContent::Fruit:
        setBrush(QBrush(Qt::red));
        break;
    case CellContent::Snake:
        setBrush(QBrush(Qt::green));
        break;
    }
}

