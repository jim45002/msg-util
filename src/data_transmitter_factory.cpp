
#include "data_transmitter.h"
#include "data_transmitter_factory.h"


data_transmitter_factory::data_transmitter_factory(QObject* parent)
    : data_transmitter_factory_interface (parent)
{

}

data_transmitter_factory::~data_transmitter_factory()
{

}

data_transmitter_interface *data_transmitter_factory::create(QString address)
{
    return new data_transmitter(address);
}

void data_transmitter_factory::destroy(data_transmitter_interface* object)
{
    delete object;
}
