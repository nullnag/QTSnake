#include "MultiPlayerDialog.h"


MultiPlayerDialog::MultiPlayerDialog(QWidget *parent)
{
    setWindowTitle("Enter username");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Enter your username:", this);
    layout->addWidget(label);

    QLineEdit* usernameLineEdit = new QLineEdit(this);
    layout->addWidget(usernameLineEdit);

    QPushButton *okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);
    connect(okButton, &QPushButton::clicked, this, [this, usernameLineEdit]() {
        emit usernameSelected(usernameLineEdit->text());
        accept();  // Закрыть диалог
    });
}
