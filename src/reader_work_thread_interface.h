#ifndef READER_WORK_THREAD_INTERFACE_H
#define READER_WORK_THREAD_INTERFACE_H

#include <memory>

#include <QThread>

class QTcpSocket;

class reader_work_thread_interface : public QThread
{
    Q_OBJECT
public:
    reader_work_thread_interface(QObject* p) : QThread(p) { }
    virtual ~reader_work_thread_interface() { }
    virtual bool connection_is_null() = 0;
    virtual void set_params(QTcpSocket* ) = 0;
    virtual void run() = 0;
};

#endif // READER_WORK_THREAD_INTERFACE_H
