#ifndef GAMEFIELDVIEW_H
#define GAMEFIELDVIEW_H

#include "GameField.h"
#include <QVector>
#include "CellView.h"
#include <QGraphicsScene>
#include <QObject>

class GameFieldView : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameFieldView(GameField* fieldModel, QObject* parent = nullptr);
public slots:
    void onFieldCleared();
    void onCellUpdate(int x, int y, CellContent content);
private:
    GameField* fieldModel;
    QVector<QVector<CellView*>> cellViews;
};

#endif // GAMEFIELDVIEW_H
