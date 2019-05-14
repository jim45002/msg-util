#ifndef DATA_TRANSMITTER_FACTORY_H
#define DATA_TRANSMITTER_FACTORY_H

#include <QObject>
#include <QString>

#include "data_transmitter_factory_interface.h"

class data_transmitter_factory : public data_transmitter_factory_interface
{
public:
    data_transmitter_factory(QObject *parent = nullptr);
    virtual ~data_transmitter_factory();

    virtual data_transmitter_interface* create(QString address);
    virtual void destroy(data_transmitter_interface*);

};

#endif // DATA_TRANSMITTER_FACTORY_H
