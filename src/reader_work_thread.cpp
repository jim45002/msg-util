
#include <QTcpSocket>

#include "packet_types.h"
#include "text_data_packet.h"
#include "voice_data_packet.h"
#include "markup_data_packet.h"
#include "reader_work_thread.h"

reader_work_thread::reader_work_thread(QObject* p)
    : reader_work_thread_interface(p),
      socket(nullptr)
{

}


//////////////////////
void reader_work_thread::set_params(QTcpSocket* s)
{
    socket = s;
}

void reader_work_thread::run()
{    
    ready_read();
    //socket->close();
    //delete socket;
    socket = nullptr;
}


//////////////////////
void reader_work_thread::ready_read()
{
    bool result = false;
    if(socket->bytesAvailable())
    {
        result=true;
    }
    else
    {
        if(socket->waitForReadyRead(60000))
        {
            result=true;
        }
        else
        {
            qDebug() << "timed out";
        }
    }

    if(true == result)
    {
        qint64 num_bytes;
        while((num_bytes=socket->bytesAvailable()))
        {
            if(num_bytes>8)
            {
                QByteArray ptype = socket->read(sizeof (int));
                QByteArray psize = socket->read(sizeof (int));
                int type = *reinterpret_cast<const int*>
                        (ptype.toStdString().c_str());
                const int size = *reinterpret_cast<const int*>
                        (psize.toStdString().c_str());
                QByteArray pdata = socket->read(size);

                qDebug() << "received packet type:" <<
                            packet_type(type) <<
                            " packet size is " <<
                            size << " bytes, read " <<
                            pdata.size() << " bytes from socket";

                bool read_error = false;
                if(size != pdata.size())
                {
                  read_error = true;
                }

                switch(type)
                {
                    case packet_type::t_text:
                    {
                       if(!read_error)
                       {
                         text_data_packet t(pdata);
                         text_packets.push_back(t);
                         process_data_packet(t);
                       }
                    }
                    break;
                    case packet_type::t_voice:
                    {
                       if(!read_error)
                       {
                          voice_data_packet v(pdata);
                          process_data_packet(v);
                       }
                    }
                    break;
                    case packet_type::t_markup:
                    {
                       if(!read_error)
                       {
                           markup_data_packet m(pdata);
                           process_data_packet(m);
                       }
                       else
                       {
                           qDebug() << "socket read error ";
                       }
                    }
                    break;
                    default:
                    {
                        qDebug() << "packet type not recognized";
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << "timed out - waiting for peer on new connection";
    }
}


////////////////////
void reader_work_thread::process_data_packet(const text_data_packet& )
{

}

void reader_work_thread::process_data_packet(const voice_data_packet& )
{

}

void reader_work_thread::process_data_packet(const markup_data_packet& )
{

}

