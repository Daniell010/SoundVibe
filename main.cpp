#include <QApplication>
#include "MyPlayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyPlayer player;
    player.show();
    return a.exec();
}
