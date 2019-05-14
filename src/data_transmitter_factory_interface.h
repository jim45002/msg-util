#ifndef DATA_TRANSMITTER_FACTORY_INTERFACE_H
#define DATA_TRANSMITTER_FACTORY_INTERFACE_H

#include <QString>

#include "data_transmitter_interface.h"

#include <QObject>

class data_transmitter_factory_interface : public QObject {
    Q_OBJECT
public:
    data_transmitter_factory_interface(QObject* parent)
        : QObject(parent) { }
    virtual ~data_transmitter_factory_interface() { }

    virtual data_transmitter_interface* create(QString address) = 0;
    virtual void destroy(data_transmitter_interface*) = 0;

};

#endif // DATA_TRANSMITTER_FACTORY_INTERFACE_H
