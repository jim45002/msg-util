#ifndef WRITER_WORK_THREAD_INTERFACE_H
#define WRITER_WORK_THREAD_INTERFACE_H

#include <QThread>

class QTcpSocket;

class writer_work_thread_interface : public QThread
{
    Q_OBJECT

public:
    writer_work_thread_interface(QObject* parent) : QThread (parent) { }
    virtual ~writer_work_thread_interface() { }

    virtual bool connection_is_null() = 0;
    virtual bool is_task_completed() = 0;
    virtual void set_params(QTcpSocket* ) = 0;
    virtual void run() = 0;

signals:
    void send_verification(QString);
    void send_status(QString);

public slots:


};

#endif // WRITER_WORK_THREAD_INTERFACE_H
