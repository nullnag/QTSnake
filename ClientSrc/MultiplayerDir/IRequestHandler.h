#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include <QString>
#include "ClientNetworkManager.h"

class IRequestHandler
{
public:
    virtual ~IRequestHandler() = default;
    virtual void handle(const QString &data) = 0;
};

class RegistrationHandle : public IRequestHandler{
public:
    explicit RegistrationHandle(ClientNetworkManager* networkManager);
    void handle(const QString &data) override;
signals:
    void registrationSuccess();
private:
    ClientNetworkManager* networkManager;
};

class CreateRoomHandle : public IRequestHandler{
public:
    explicit CreateRoomHandle(ClientNetworkManager* networkManager);
    void handle(const QString &data) override;
signals:
    void registrationSuccess();
private:
    ClientNetworkManager* networkManager;
};

#endif // IREQUESTHANDLER_H
