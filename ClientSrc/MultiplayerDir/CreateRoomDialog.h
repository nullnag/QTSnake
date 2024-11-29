#ifndef CREATEROOMDIALOG_H
#define CREATEROOMDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QPushButton>

class CreateRoomDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateRoomDialog(QWidget* parent = nullptr);
    int getPlayerCount() const;
    int getFieldSize() const;
private:
    QSpinBox* playerCountSpinBox;
    QSpinBox* fieldSizeSpinBox;
    QPushButton* okButton;
    QPushButton* cancelButton;
private slots:
    void onOkClicked();
};

#endif // CREATEROOMDIALOG_H
