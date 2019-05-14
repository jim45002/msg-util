#ifndef DATA_RECEIVER_FACTORY_INTERFACE_H
#define DATA_RECEIVER_FACTORY_INTERFACE_H

#include <QObject>

class data_receiver_interface;

class data_receiver_factory_interface : public QObject
{
    Q_OBJECT
public:
    data_receiver_factory_interface(QObject* parent) : QObject(parent) { }
    virtual ~data_receiver_factory_interface() { }

    virtual data_receiver_interface* create(QObject* parent) = 0;
    virtual void destroy(data_receiver_interface*) = 0;

};

#endif // DATA_RECEIVER_FACTORY_INTERFACE_H
