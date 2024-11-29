#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include "ClientNetworkManager.h"
#include "CreateRoomDialog.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MultiplayerMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MultiplayerMenu(QWidget* parent = nullptr, ClientNetworkManager* networkManager = nullptr, QString username = 0);
    void createRoom();
signals:
    void joinRoom();
    void backToMainMenu();
private:
    CreateRoomDialog* createRoomDialog;
    ClientNetworkManager* networkManager;
    QString username;
};

#endif // MULTIPLAYERMENU_H
