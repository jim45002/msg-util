#ifndef DATA_RECEIVER_FACTORY_H
#define DATA_RECEIVER_FACTORY_H

#include "data_receiver_factory_interface.h"

class data_receiver_factory : public data_receiver_factory_interface
{
public:
    data_receiver_factory(QObject *parent);
    virtual ~data_receiver_factory();

    virtual data_receiver_interface* create(QObject* parent);
    virtual void destroy(data_receiver_interface* object);
};

#endif // DATA_RECEIVER_FACTORY_H
