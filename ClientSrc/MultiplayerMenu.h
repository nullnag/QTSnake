#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class MultiplayerMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MultiplayerMenu(QWidget* parent = nullptr);
signals:
    void createRoom();
    void joinRoom();
    void backToMainMenu();
};

#endif // MULTIPLAYERMENU_H
