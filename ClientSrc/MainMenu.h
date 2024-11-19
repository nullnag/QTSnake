#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class MainMenu : public QWidget
{
public:
    MainMenu();
public slots:
    void singleplayerButtonPressed();
    void onSizeSelected(int size);
};

#endif // MAINMENU_H
