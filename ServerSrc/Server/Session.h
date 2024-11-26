#ifndef SESSION_H
#define SESSION_H

#include "QHash"
#include <QTimer>
#include <QHostAddress>
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
    QList<QString> getPlayers();
    void updateGameState();
    Snake* getSnakeByNickName(const QString& nickname);
    QByteArray serializeGameState() const;
private:
    int countOfPlayers;
    int fieldSize;
    QHash<QString,Snake*> snakes;
    QTimer* gameUpdateTimer;
};

#endif // SESSION_H
