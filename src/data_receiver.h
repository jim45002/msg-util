#ifndef DATA_RECEIVER_H
#define DATA_RECEIVER_H

#include <memory>

#include <QAbstractSocket>

#include "data_receiver_interface.h"

class QTcpServer;
class QTcpSocket;
class reader_work_thread_interface;


class data_receiver : public data_receiver_interface
{
    Q_OBJECT
public:
    data_receiver(QObject *p);
    virtual ~data_receiver();

    std::shared_ptr<reader_work_thread_interface>
    find_worker_thread();

public slots:
    void newConnection();

private:
   QList<std::shared_ptr
   <reader_work_thread_interface>> work_thread_list;
   std::shared_ptr<QTcpServer> tcp_server;
};

#endif // DATA_RECEIVER_H
