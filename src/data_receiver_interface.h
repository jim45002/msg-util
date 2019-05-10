#ifndef DATA_RECEIVER_INTERFACE_H
#define DATA_RECEIVER_INTERFACE_H

#include <QObject>

class data_receiver_interface : public QObject
{
    Q_OBJECT
public:
    data_receiver_interface(QObject* p) : QObject(p) { }
    virtual ~data_receiver_interface() {}

signals:

public slots:


};

#endif // DATA_RECEIVER_INTERFACE_H
