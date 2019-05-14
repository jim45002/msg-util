#include <memory>

#include <QApplication>

#include "data_transmitter_factory.h"
#include "messenger_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto f = std::make_shared<data_transmitter_factory>();

    messenger_dialog m(f);
    m.show();
    return a.exec();
}
