#include "GameWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.setFixedSize(805, 805);

    w.show();
    return a.exec();
}
