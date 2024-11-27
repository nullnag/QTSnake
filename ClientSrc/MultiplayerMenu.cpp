#include "MultiplayerMenu.h"


MultiplayerMenu::MultiplayerMenu(QWidget *parent)
{
    setWindowTitle("Multiplayer Menu");
    setFixedSize(300, 200);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Multiplayer Menu", this);
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignCenter);

    QPushButton* createRoomButton = new QPushButton("Create Room", this);
    QPushButton* joinRoomButton = new QPushButton("Join Room", this);
    QPushButton* backButton = new QPushButton("Back to Main Menu", this);

    layout->addWidget(createRoomButton);
    layout->addWidget(joinRoomButton);
    layout->addWidget(backButton);

    // Подключаем кнопки к соответствующим действиям
    connect(createRoomButton, &QPushButton::clicked, this, &MultiplayerMenu::createRoom);
    connect(joinRoomButton, &QPushButton::clicked, this, &MultiplayerMenu::joinRoom);
    connect(backButton, &QPushButton::clicked, this, &MultiplayerMenu::backToMainMenu);
}
