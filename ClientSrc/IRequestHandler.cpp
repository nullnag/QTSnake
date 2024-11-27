#include "IRequestHandler.h"

RegistrationHandle::RegistrationHandle(ClientNetworkManager *networkManager) : networkManager(networkManager)
{

}

void RegistrationHandle::handle(const QString &data)
{
    if (data == "Player registered") {
        networkManager->openMultiPlayerMenu();
    }
}
