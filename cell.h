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
    int mX, mY;
    CellContent m_content;
    void updateBrush();
    static const QMap<CellContent,QBrush> brushMap;
};

#endif // CELL_H
