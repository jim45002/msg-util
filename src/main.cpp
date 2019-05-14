#include <memory>

#include <QApplication>

#include "data_transmitter_factory.h"
#include "data_receiver_factory.h"
#include "messenger_dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto trans_factory = std::make_shared<data_transmitter_factory>();
    auto recv_factory = std::make_shared<data_receiver_factory>(nullptr);
    auto receiver = recv_factory->create(nullptr);
    messenger_dialog m(trans_factory,receiver);
    m.show();
    auto result = a.exec();
    recv_factory->destroy(receiver);
    return result;
}
