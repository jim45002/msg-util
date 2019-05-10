
#include <QApplication>

#include "messenger_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    messenger_dialog m;
    m.show();

    return a.exec();
}
