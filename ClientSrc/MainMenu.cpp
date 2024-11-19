#include "MainMenu.h"
#include "GameWindow.h"
#include "GameSizeDialogue.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

MainMenu::MainMenu() {
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

}

void MainMenu::singleplayerButtonPressed()
{
    GameSizeDialogue *dialog = new GameSizeDialogue(this);
    connect(dialog, &GameSizeDialogue::sizeSelected, this, &MainMenu::onSizeSelected);
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
