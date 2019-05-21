#ifndef WRITER_WORK_THREAD_H
#define WRITER_WORK_THREAD_H

#include <memory>

#include <QThread>
#include <QObject>

#include "packet_types.h"
//#include "text_data_packet.h"
//#include "voice_data_packet.h"
//#include "markup_data_packet.h"

#include "writer_work_thread_interface.h"

class text_data_packet;
class voice_data_packet;
class markup_data_packet;
class QTcpSocket;

class writer_work_thread : public writer_work_thread_interface
{
    Q_OBJECT

public:
    writer_work_thread(QObject *parent);
    virtual ~writer_work_thread();

    virtual bool connection_is_null() { return (!socket)?true:false; }
    virtual void set_params(QTcpSocket* );
    virtual bool is_task_completed();
    virtual void run();
    QByteArray make_data_packet(const QByteArray b, packet_type t);
    void process_data_packet(const text_data_packet &data);
    void process_data_packet(const voice_data_packet &data);
    void process_data_packet(const markup_data_packet &data);

public slots:
    virtual void ready_write();
private:
    bool task_completed;
    QTcpSocket* socket;
    QList<text_data_packet> text_packets;
    QList<voice_data_packet> voice_packets;
    QList<markup_data_packet> markup_packets;
};

#endif // WRITER_WORK_THREAD_H
