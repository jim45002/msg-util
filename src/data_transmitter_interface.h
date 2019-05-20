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
    virtual bool is_finished() = 0;
signals:
    void send_completed(QString);
    void connection_status_update(QString);
    void received_verification(QString);

public slots:

private:

};

#endif // DATA_TRANSMITTER_INTERFACE_H
