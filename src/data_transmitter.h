#ifndef DATA_TRANSMITTER_H
#define DATA_TRANSMITTER_H

#include <memory>

#include "data_transmitter_interface.h"

class QNetworkProxy;
class QTcpSocket;
class writer_work_thread_interface;

class data_transmitter : public data_transmitter_interface
{
    Q_OBJECT
public:
    explicit data_transmitter(QString receiving_peer, QObject *parent = nullptr);
    virtual ~data_transmitter() { }

    virtual bool is_finished();
    std::shared_ptr
    <writer_work_thread_interface> find_worker_thread();

public slots:
    virtual void connected_to_host_completed();
    virtual void on_send_verification(QString);
    virtual void on_send_status(QString);

private:
    QList<std::shared_ptr
    <writer_work_thread_interface>> work_thread_list;
    std::shared_ptr<QTcpSocket> tcp_socket;
    QNetworkProxy* network_proxy;
    QString receiving_peer_address;
};

#endif // DATA_TRANSMITTER_H
