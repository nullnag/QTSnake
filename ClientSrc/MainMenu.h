#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "ClientNetworkManager.h"
#include "MultiplayerMenu.h"

class MainMenu : public QWidget
{
public:
    MainMenu();
public slots:
    void singleplayerButtonPressed();
    void multiplayerButtonPressed();
    void onSizeSelected(int size);
    void onUsernameSelected(QString username);
    void openMultiPlayerMenu();
private:
    ClientNetworkManager* networkManager;
    QString username;
};

#endif // MAINMENU_H
