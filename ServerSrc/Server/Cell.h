#ifndef CELL_H
#define CELL_H

#include <QObject>

enum class CellContent
{
    Empty,
    Fruit,
    Snake
};

class Cell : public QObject
{
    Q_OBJECT
public:
    Cell(QObject* parent = nullptr, int x = 0, int y = 0);
    void setContent(CellContent content);
    CellContent getContent() const;
    bool isEmpty();
    int getX();
    int getY();
    void removeContent();
signals:
    void contentChanged(int x, int y, CellContent content);
private:
    int startX, startY;
    CellContent m_content;
};

#endif // CELL_H
