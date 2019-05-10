#ifndef READER_WORK_THREAD_H
#define READER_WORK_THREAD_H

#include <memory>

#include <QThread>

#include "text_data_packet.h"
#include "voice_data_packet.h"
#include "markup_data_packet.h"
#include "reader_work_thread_interface.h"

class text_data_packet;
class voice_data_packet;
class markup_data_packet;

class QTcpSocket;

class reader_work_thread : public reader_work_thread_interface
{
    Q_OBJECT
public:
    reader_work_thread(QObject* = nullptr);
    virtual ~reader_work_thread() { }

public:
    virtual bool connection_is_null() { return (!socket)?true:false; }
    virtual void set_params(QTcpSocket* );
    virtual void run();
    void process_data_packet(const text_data_packet &data);
    void process_data_packet(const voice_data_packet &data);
    void process_data_packet(const markup_data_packet &data);

public slots:
    virtual void ready_read();

private:

    QTcpSocket* socket;
    QList<text_data_packet> text_packets;
    QList<voice_data_packet> voice_packets;
    QList<markup_data_packet> markup_packets;
};

#endif // READER_WORK_THREAD_H
