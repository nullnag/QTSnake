#include "GameOverDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

GameOverDialog::GameOverDialog(const QString &message, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Game Over");
    setFixedSize(200,100);
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(message,this);
    QPushButton* restartButton = new QPushButton("Restart",this);
    QPushButton* exitButton = new QPushButton("Exit",this);

    layout->addWidget(label);
    layout->addWidget(restartButton);
    layout->addWidget(exitButton);

    connect(restartButton, &QPushButton::clicked, this, &GameOverDialog::accept);
    connect(exitButton, &QPushButton::clicked,this, &GameOverDialog::reject);
}
