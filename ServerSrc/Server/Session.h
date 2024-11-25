#ifndef SESSION_H
#define SESSION_H

#include "QHash"
#include <QTimer>
#include "Snake.h"

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject* parent = nullptr,int countOfPlayers = 2,int fieldSize = 16);
    ~Session();
    void startGame();
    void addPlayer(const QString& nickname);
    void deletePlayer(const QString& nickname);
    bool hasPlayer(const QString& nickname);
    void updateGameState();
    Snake* getSnakeByNickName(const QString& nickname);
private:
    int countOfPlayers;
    int fieldSize;
    QHash<QString,Snake*> snakes;
    QTimer* gameUpdateTimer;
    QByteArray serializeGameState() const;
};

#endif // SESSION_H
