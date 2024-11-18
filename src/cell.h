#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

enum class CellContent
{
    Empty,
    Fruit,
    Snake
};

class Cell : public QGraphicsRectItem
{
public:
    Cell(QGraphicsItem* parent = nullptr, int x = 0, int y = 0);
    void setContent(CellContent content);
    CellContent getContent() const;
    bool isEmpty();
    QPoint getPosition() const;
    void removeContent();
private:
    int startX, startY;
    CellContent m_content;
    void updateBrush();
};

#endif // CELL_H
