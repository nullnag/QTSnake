#include "GameSizeDialogue.h"

GameSizeDialogue::GameSizeDialogue(QWidget *parent)
{
    setWindowTitle("Select Game Field Size");

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Select field size (NxN):", this);
    layout->addWidget(label);

    // Поле для выбора размера
    QSpinBox *sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(5, 20);  // Например, поле от 5x5 до 20x20
    layout->addWidget(sizeSpinBox);

    // Кнопка подтверждения
    QPushButton *okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, [this, sizeSpinBox]() {
        emit sizeSelected(sizeSpinBox->value());
        accept();  // Закрыть диалог
    });
}
