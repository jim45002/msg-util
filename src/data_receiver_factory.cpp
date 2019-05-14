
#include "data_receiver.h"
#include "data_receiver_factory.h"

data_receiver_factory::data_receiver_factory(QObject* parent)
    : data_receiver_factory_interface(parent)
{

}

data_receiver_factory::~data_receiver_factory()
{

}

data_receiver_interface* data_receiver_factory::create(QObject* parent)
{
    return new data_receiver(parent);
}

void data_receiver_factory::destroy(data_receiver_interface* object)
{
    delete object;
}
