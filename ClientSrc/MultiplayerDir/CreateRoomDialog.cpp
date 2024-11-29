#include "CreateRoomDialog.h"
#include <QVBoxLayout>
#include <QLabel>

CreateRoomDialog::CreateRoomDialog(QWidget *parent) : QDialog(parent)
{
    playerCountSpinBox = new QSpinBox(this);
    fieldSizeSpinBox = new QSpinBox(this);
    okButton = new QPushButton("OK",this);
    cancelButton = new QPushButton("Cancle",this);
    playerCountSpinBox->setRange(1, 4);
    playerCountSpinBox->setValue(2);

    fieldSizeSpinBox->setRange(5, 20);
    fieldSizeSpinBox->setValue(10);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Количество игроков:"));
    layout->addWidget(playerCountSpinBox);
    layout->addWidget(new QLabel("Размер поля:"));
    layout->addWidget(fieldSizeSpinBox);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &CreateRoomDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CreateRoomDialog::reject);
}

int CreateRoomDialog::getPlayerCount() const
{
    return playerCountSpinBox->value();
}

int CreateRoomDialog::getFieldSize() const
{
    return fieldSizeSpinBox->value();
}

void CreateRoomDialog::onOkClicked()
{
    accept();
}
