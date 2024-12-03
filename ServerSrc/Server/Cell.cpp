#include "Cell.h"

Cell::Cell(QObject* parent , int x, int y)  : QObject(parent), m_content(CellContent::Empty), startX(x), startY(y) {

}

void Cell::setContent(CellContent content)
{
    m_content = content;
}

CellContent Cell::getContent() const
{
    return m_content;
}

bool Cell::isEmpty()
{
    return m_content == CellContent::Empty;
}

int Cell::getX()
{
    return startX;
}

int Cell::getY()
{
    return startY;
}

void Cell::removeContent()
{
    setContent(CellContent::Empty);
}


