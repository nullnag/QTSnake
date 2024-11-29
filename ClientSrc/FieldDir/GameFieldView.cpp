#include "GameFieldView.h"


GameFieldView::GameFieldView(GameField *fieldModel, QObject *parent) : QGraphicsScene(parent), fieldModel(fieldModel)
{
    connect (fieldModel, &GameField::fieldCleared, this, &GameFieldView::onFieldCleared);
    connect (fieldModel, &GameField::cellUpdated, this, &GameFieldView::onCellUpdate);
    int size = fieldModel->getSize();
    cellViews.resize(size);
    for (int x = 0; x < size; ++x) {
        cellViews[x].resize(size);
        for (int y = 0; y < size; ++y) {
            CellView* view = new CellView(fieldModel->getCell(x, y));
            addItem(view);
            cellViews[x][y] = view;
        }
    }
}

void GameFieldView::onFieldCleared() {
    for (auto& row : cellViews) {
        for (auto& cell : row) {
            cell->updateContent(-1, -1, CellContent::Empty);
        }
    }
}

void GameFieldView::onCellUpdate(int x, int y, CellContent content) {
    cellViews[x][y]->updateContent(x, y, content);
}
