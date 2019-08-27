
#include <QTcpSocket>

#include "packet_types.h"
#include "text_data_packet.h"
#include "voice_data_packet.h"
#include "markup_data_packet.h"
#include "image_data_packet.h"
#include "reader_work_thread.h"
#include "recv_error_text_data_packet.h"
#include "send_error_text_data_packet.h"

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
    socket = nullptr;
}

//////////////////////

void reader_work_thread::read_packet_data(QByteArray& bytes)
{

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
        if(socket->waitForReadyRead(30000))
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
       QByteArray identifer;
       if((num_bytes=socket->bytesAvailable()))
        {
            if(num_bytes>8)
            {                
                QByteArray ptype = socket->read(sizeof (int));
                QByteArray psize = socket->read(sizeof (int));
                QByteArray idsize = socket->read(sizeof (int));

                int type = *reinterpret_cast<const int*>
                        (ptype.data());

                const int size = *reinterpret_cast<const int*>
                        (psize.data());

                const int identifer_size = *reinterpret_cast<const int*>
                        (idsize.data());

                QByteArray pdata;
                pdata.resize(size);
                long long num_read = 0;
                for(int tries=0;(num_read!=size)&&(num_read<size);++tries)
                {
                   if(socket->bytesAvailable())
                   {
                      long long num =
                            socket->read(pdata.data()+num_read,(size-num_read));

                      if(num > -1)
                      {
                         num_read += num;

                         qDebug() << "num read == " << num_read;
                         if(num_read>size)
                         {
                             qDebug() << "error on read - num_read > size "
                                      << num_read;
                             break;
                         }
                         else
                         if(num_read == size)
                         {
                             qDebug() << "completed data read - "
                                      << num_read;

                             qDebug() << "reading idetifier";
                             identifer = socket->read(identifer_size);
                             if(identifer.size() != identifer_size)
                             {
                                 qDebug() << "error reading identifer -> identifier_size == "
                                          << identifer_size
                                          << " identifier.size() == "
                                          << identifer.size();
                             }
                             break;
                         }
                         else
                         if(num_read<size)
                         {
                             qDebug() << "num_read < size  - size "
                                      << size
                                      << ", num_read  "
                                      << num_read;
                         }
                      }
                      else
                      {
                         qDebug() << "error occured while reading socket";
                      }
                   }
                   else
                   {
                      qDebug() << "waiting for ready read, " << num_read;
                      socket->waitForReadyRead(3000);
                   }

                   if(tries>32)
                   {
                      qDebug() << "max attempts to read data";
                      break;
                   }
                }

                qDebug() << "received packet type:"
                         << packet_type(type)
                         << " packet size is "
                         << size
                         << " bytes, read "
                         << num_read
                         << " bytes from socket";

                qDebug() << "identifier_size == "
                         << identifer_size
                         << " identifier.size() == "
                         << identifer.size();

                bool read_error = false;
                if((size != num_read) || (identifer.size() != identifer_size))
                {
                  read_error = true;
                  qDebug() << "error occured: "
                              "(size != num_read) || (identifer.size() != identifer_size) ";
                }

                switch(type)
                {
                case packet_type::t_image:
                {
                   if(!read_error)
                   {
                     image_data_packet i(pdata);
                     process_data_packet(i);
                   }
                }
                break;
                case packet_type::t_text:
                {
                   if(!read_error)
                   {
                     text_data_packet t(pdata);
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
                case packet_type::t_recv_text_error:
                {
                   recv_error_text_data_packet m(pdata);
                   process_data_packet(m);
                }
                break;
                case packet_type::t_send_text_error:
                {
                   send_error_text_data_packet m(pdata);
                   process_data_packet(m);
                }
                break;
                default:
                {
                   qDebug() << "packet type not recognized";
                }
                }
            }
        }
        else
        {
           qDebug() << "not enough data sent to socket";
        }
    }
    else
    {
        qDebug() << "timed out - waiting for peer on new connection";
    }
}


////////////////////

void reader_work_thread::process_data_packet(const image_data_packet& )
{

}

void reader_work_thread::process_data_packet(const text_data_packet& )
{

}

void reader_work_thread::process_data_packet(const voice_data_packet& )
{

}

void reader_work_thread::process_data_packet(const markup_data_packet& )
{

}

void reader_work_thread::process_data_packet(const recv_error_text_data_packet& )
{

}

void reader_work_thread::process_data_packet(const send_error_text_data_packet& )
{

}
