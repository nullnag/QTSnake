#ifndef MULTIPLAYERDIALOG_H
#define MULTIPLAYERDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


class MultiPlayerDialog : public QDialog
{
    Q_OBJECT
public:
    MultiPlayerDialog(QWidget* parent = nullptr);
signals:
    void usernameSelected(QString username);
};

#endif // MULTIPLAYERDIALOG_H
