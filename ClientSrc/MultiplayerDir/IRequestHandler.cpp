#include "IRequestHandler.h"
#include "MultiPlayerGame.h"
#include <QJsonDocument>
#include <QJsonObject>

RegistrationHandle::RegistrationHandle(ClientNetworkManager *networkManager) : networkManager(networkManager) {}

void RegistrationHandle::handle(const QString &data)
{
    networkManager->openMultiPlayerMenu();
}

CreateRoomHandle::CreateRoomHandle(ClientNetworkManager *networkManager) : networkManager(networkManager) {}

void CreateRoomHandle::handle(const QString &data)
{
    qDebug() << "Room created";
}

GameStateHandle::GameStateHandle(ClientNetworkManager *networkManager) : networkManager(networkManager)
{

}

void GameStateHandle::handle(const QString &data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (doc.isObject()) {
        QJsonObject gameState = doc.object();

        // Проверяем тип сообщения и вызываем соответствующий метод для обновления игры

            // Получаем объект MultiPlayerGame
        MultiPlayerGame* game = networkManager->getGameInstance();
        if (game) {
            game->updateGame(gameState);  // Передаем QJsonObject в метод обновления игры
        }

    }
    else {
        qWarning() << "Failed to parse game state JSON";
    }
}
