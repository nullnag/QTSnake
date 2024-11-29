#ifndef GAMESIZEDIALOGUE_H
#define GAMESIZEDIALOGUE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

class GameSizeDialogue : public QDialog
{
    Q_OBJECT
public:
    GameSizeDialogue(QWidget* parent = nullptr);
signals:
    void sizeSelected(int size);
};

#endif // GAMESIZEDIALOGUE_H
