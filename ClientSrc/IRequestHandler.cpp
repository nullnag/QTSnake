#include "IRequestHandler.h"

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
