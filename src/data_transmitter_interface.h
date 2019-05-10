#ifndef DATA_TRANSMITTER_INTERFACE_H
#define DATA_TRANSMITTER_INTERFACE_H

#include <thread>
#include <chrono>

#include <QBitArray>
#include <QTcpSocket>
#include <QNetworkProxy>
#include <QObject>

class data_transmitter_interface : public QObject
{
    Q_OBJECT
public:
    data_transmitter_interface(QObject* parent) : QObject(parent) { }
    virtual ~data_transmitter_interface() { }

signals:

public slots:

};

#endif // DATA_TRANSMITTER_INTERFACE_H
