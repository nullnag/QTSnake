#include "MultiplayerMenu.h"
#include "CreateRoomDialog.h"
#include "MultiPlayerGame.h"
#include "GameWindow.h"

MultiplayerMenu::MultiplayerMenu(QWidget *parent, ClientNetworkManager *networkManager, QString username) :
    networkManager(networkManager),
    username(username)

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


// Формат команды: "CREATE_SESSION:<leaderName>:<countOfPlayers>:<fieldSize>"
void MultiplayerMenu::createRoom(){
    createRoomDialog = new CreateRoomDialog(this);
    if (createRoomDialog->exec() == QDialog::Accepted){
        int playersCount = createRoomDialog->getPlayerCount();
        int fieldSize = createRoomDialog->getFieldSize();
        QByteArray message = QString("CREATE_SESSION:%1:%2:%3")
                                 .arg(username.trimmed())
                                 .arg(playersCount)
                                 .arg(fieldSize)
                                 .toUtf8();
        if (!networkManager){
            qDebug() << "Network manager is nullptr";
        }
        networkManager->sendMessage(message);

        IGame* multiPlayerGame = new MultiPlayerGame();
        IInputHandler* multiplayerInputHandler = new MultiPlayerInputHandler();
        GameWindow* gameWindow = new GameWindow(this,fieldSize,multiPlayerGame, multiplayerInputHandler);

        int cellSize = 50;
        int newWidth = fieldSize * cellSize + 20;
        int newHeight = fieldSize * cellSize + 50;

        gameWindow->setFixedSize(newWidth, newHeight);
        gameWindow->setAttribute(Qt::WA_DeleteOnClose);

        gameWindow->show();
    }
}
