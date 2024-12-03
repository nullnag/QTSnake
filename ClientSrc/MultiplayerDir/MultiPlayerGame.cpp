#include "MultiPlayerGame.h"
#include <QJsonObject>
#include <QJsonArray>

MultiPlayerGame::~MultiPlayerGame()
{

}

void MultiPlayerGame::restartGame()
{

}

void MultiPlayerGame::endGame()
{

}

void MultiPlayerGame::initialize(GameField *gameField, GameWindow *parentWindow)
{
    this->gameField = gameField;
    this->parentWindow = parentWindow;
}

void MultiPlayerGame::startGame()
{

}

Snake *MultiPlayerGame::getSnake()
{
    return nullptr;
}

void MultiPlayerGame::updateGame(const QJsonObject& gameState)
{
    qDebug() << "Update game state";
    clearSnakeFromField();
    QJsonObject snakesJson = gameState["snakes"].toObject();

    // Проходим по всем змейкам в игре
    for (auto it = snakesJson.begin(); it != snakesJson.end(); ++it) {
        QString playerName = it.key();  // Имя игрока
        QJsonArray snakeBody = it.value().toArray();  // Тело змейки (массив координат)

        // Очистим старое состояние змейки

        // Обновляем клетки для новой позиции змейки
        for (const QJsonValue& segmentValue : snakeBody) {
            QJsonObject segment = segmentValue.toObject();
            int x = segment["x"].toInt();
            int y = segment["y"].toInt();

            // Находим клетку по координатам и обновляем ее содержимое
            if (gameField->getCell(x,y)){
                gameField->getCell(x, y)->setContent(CellContent::Snake);
            }
        }
    }
}

void MultiPlayerGame::clearSnakeFromField()
{
    int fieldSize = gameField->getSize(); // Получаем размер игрового поля
    for (int x = 0; x < fieldSize; ++x) {
        for (int y = 0; y < fieldSize; ++y) {
            Cell* cell = gameField->getCell(x, y);
            if (cell && cell->getContent() == CellContent::Snake) {
                cell->setContent(CellContent::Empty); // Сбрасываем клетку
            }
        }
    }
}

void MultiPlayerGame::spawnFood()
{

}
