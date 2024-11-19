#include "GameWindow.h"
#include "MainMenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GameWindow w;
    MainMenu menu;
    menu.show();
    //w.setFixedSize(805, 805);

    //w.show();
    return a.exec();
}
