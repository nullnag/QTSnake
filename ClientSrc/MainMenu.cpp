#include "MainMenu.h"
#include "GameWindow.h"
#include "GameSizeDialogue.h"
#include "MultiPlayerDialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

MainMenu::MainMenu() {
    networkManager = new ClientNetworkManager(this);
    setWindowTitle("Main Menu");
    setFixedSize(200,100);
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* mainMenuLabel = new QLabel("Main Menu",this);
    QPushButton* singlePlayerButton = new QPushButton("Singleplayer game",this);
    QPushButton* multiPlayerButton = new QPushButton("Multiplayer game",this);
    layout->addWidget(mainMenuLabel);
    layout->addWidget(singlePlayerButton);
    layout->addWidget(multiPlayerButton);

    layout->setAlignment(mainMenuLabel,Qt::AlignCenter);

    connect(singlePlayerButton,&QPushButton::clicked,this,&MainMenu::singleplayerButtonPressed);
    connect(multiPlayerButton,&QPushButton::clicked,this,&MainMenu::multiplayerButtonPressed);
    connect(networkManager,&ClientNetworkManager::openMultiPlayerMenu,this,&MainMenu::openMultiPlayerMenu);

}

void MainMenu::singleplayerButtonPressed()
{
    GameSizeDialogue *dialog = new GameSizeDialogue(this);
    connect(dialog, &GameSizeDialogue::sizeSelected, this, &MainMenu::onSizeSelected);
    dialog->setFixedSize(200,100);
    dialog->exec();
}

void MainMenu::multiplayerButtonPressed()
{
    MultiPlayerDialog *dialog = new MultiPlayerDialog(this);
    connect(dialog, &MultiPlayerDialog::usernameSelected, this, &MainMenu::onUsernameSelected);
    dialog->setFixedSize(200,100);
    dialog->exec();
}

void MainMenu::onSizeSelected(int size)
{
    GameWindow* gameWindow = new GameWindow(this,size);

    int cellSize = 50;
    int newWidth = size * cellSize + 20;
    int newHeight = size * cellSize + 50;

    gameWindow->setFixedSize(newWidth, newHeight);
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);

    gameWindow->show();
}

void MainMenu::onUsernameSelected(QString username)
{
    networkManager->connectToServer(QHostAddress("127.0.0.1"),12345,username);
}

void MainMenu::openMultiPlayerMenu()
{
    MultiplayerMenu* multiplayerMenu = new MultiplayerMenu(this);
    multiplayerMenu->setFixedSize(300, 200);
    multiplayerMenu->setAttribute(Qt::WA_DeleteOnClose);

    multiplayerMenu->show();
    qDebug()  << "Успех открываю окно";
}
