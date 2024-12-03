#ifndef SESSION_H
#define SESSION_H

#include "QHash"
#include <QTimer>
#include <QHostAddress>
#include "Snake.h"

class Game;

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* parent = nullptr,int countOfPlayers = 2,int fieldSize = 16);
    ~Session();
    void startGame();
    void stopGame();
    void addPlayer(const QString& nickname);
    void deletePlayer(const QString& nickname);
    GameField* getGameField();
    bool hasPlayer(const QString& nickname);
    QList<QString> getPlayers() const ;
    Snake* getSnakeByNickName(const QString& nickname) const;
    QHash<QString, Snake*> getSnakes();
    QPoint getUniqueSpawnPosition();
    bool isPositionFree(const QPoint& position);
    QByteArray serializeGameState() const;
    void onGameTick();
signals:
    void updateGameState();
private:
    int countOfPlayers;
    int fieldSize;
    QHash<QString,Snake*> snakes;
    Game* game;
    GameField* gameField;
    QTimer* gameUpdateTimer;
};

#endif // SESSION_H
