#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

class GameOverDialog : public QDialog
{
    Q_OBJECT
public:
    GameOverDialog(const QString& message, QWidget* parent = nullptr);
};

#endif // GAMEOVERDIALOG_H
