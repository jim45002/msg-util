
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QDataStream>

#include "packet_types.h"
#include "text_data_packet.h"
#include "voice_data_packet.h"
#include "markup_data_packet.h"
#include "Encoder.h"
#include "writer_work_thread.h"

writer_work_thread::writer_work_thread(QObject* parent)
    : writer_work_thread_interface (parent),
      task_completed(false),
      socket(nullptr)
{

}

writer_work_thread::~writer_work_thread()
{

}

//////////////////////
void writer_work_thread::set_params(QTcpSocket* s)
{
     socket = s;
}

bool writer_work_thread::is_task_completed()
{
    return task_completed;
}

void writer_work_thread::run()
{
    ready_write();
    task_completed=true;
}

QByteArray writer_work_thread::make_data_packet(const QByteArray b,
                                                packet_type t)
{
    QByteArray packet;
    switch(t)
    {
    case packet_type::t_video:
    {
        packet_type data_packet_type = t;
        int packet_size = b.size();
        packet.append(reinterpret_cast<char*>(&data_packet_type),
                      sizeof(int));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.data(),packet_size);
    }
        break;
    case packet_type::t_image:
    {
        packet_type data_packet_type = t;
        int packet_size = b.size();
        packet.append(reinterpret_cast<char*>(&data_packet_type),
                      sizeof(int));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.data(),packet_size);
    }
        break;
    case packet_type::t_voice:
    {
        packet_type data_packet_type = t;
        int packet_size = b.size();       
        packet.append(reinterpret_cast<char*>(&data_packet_type),
                      sizeof(int));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.data(),packet_size);
    }
        break;
    case packet_type::t_text:
    {
        packet_type data_packet_type = t;
        int packet_size = b.size();                
        packet.append(reinterpret_cast<char*>(&data_packet_type),
                      sizeof(int));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.data(),packet_size);
    }
        break;
    case packet_type::t_markup:
    {
        packet_type data_packet_type = t;
        int packet_size = b.size();
        packet.append(reinterpret_cast<char*>(&data_packet_type),
                      sizeof(int));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.data(),packet_size);
    }
        break;
    }
    return packet;
}

bool writer_work_thread::send_packet_data(QByteArray& bytes)
{
    bool result = true;

    if(bytes.size())
    {
        long long num_written=0;
        int tries=0;
        for(;num_written<bytes.size();++tries)
        {
           long long num =
                   socket->write(bytes.data()+num_written,
                                 bytes.size()-num_written);
           if(num > -1)
           {
               qDebug() << "wrote " << num << " bytes to socket";
               num_written += num;
               if(num_written<bytes.size())
               {
                 qDebug() << " num bytes written < size "
                          << num_written
                          << " bytes";
               }
               else
               {
                   if(num_written==bytes.size())
                   {
                       qDebug() << "completed data write";
                       break;
                   }
                   else
                   if(num_written>bytes.size())
                   {
                       qDebug() << "num bytes written > buff size";
                       result = false;
                       break;
                   }
               }
           }
           else
           {
               qDebug() << "error occured while sending data";
               result = false;
           }
          if(tries>16)
           {
               qDebug() << "max send attempts";
               result = false;
               break;
           }
        }
    }
    else
    {
        result = false;
    }

    return result;
}

//////////////////////
void writer_work_thread::ready_write()
{
    auto send_image_data = [this] ()
    {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_image_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.bz2";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        for(auto file : files)
        {
            QFile f(QString("./outgoing_image_data/")+file);
            if(f.open(QIODevice::ReadOnly))
            {
                QByteArray bytes = f.readAll();
                bytes=make_data_packet(bytes,packet_type::t_image);
                if(send_packet_data(bytes))
                {
                   f.remove();
                }
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

    auto send_map_markup_data = [this]() {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_map_markup_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.bz2";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        for(auto file : files)
        {
            QFile f(QString("./outgoing_map_markup_data/")+file);
            if(f.open(QIODevice::ReadOnly))
            {
                QByteArray bytes = f.readAll();
                bytes=make_data_packet(bytes,packet_type::t_markup);
                if(bytes.size())
                {
                    if(send_packet_data(bytes))
                    {
                       f.remove();
                    }
                }
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

    auto send_voice_data = [this]() {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_voice_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.voc";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        for(auto file : files)
        {
            QFile f(QString("./outgoing_voice_data/")+file);
            if(f.open(QIODevice::ReadOnly))
            {
                QByteArray bytes = f.readAll();
                QDataStream stream(bytes);
                Encoder encoder(stream);
                bytes = encoder.OutputBuffer();
                bytes=make_data_packet(bytes,packet_type::t_voice);
                if(bytes.size())
                {
                    if(send_packet_data(bytes))
                    {
                       f.remove();
                    }
                }
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

    auto send_text_data = [this]() {
        QDir directory;
        directory.setFilter(QDir::Files);
        directory.setPath(QString("./outgoing_text_data"));
        directory.setSorting(QDir::Time);
        QStringList name_filter;
        name_filter << "*.txt";
        directory.setNameFilters(name_filter);
        QStringList files =
                directory.entryList(QDir::Files,QDir::Time);

        for(auto file : files)
        {
            QFile f(QString("./outgoing_text_data/")+file);
            if(f.open(QIODevice::ReadOnly))
            {
                QByteArray bytes = f.readAll();
                bytes=make_data_packet(bytes,packet_type::t_text);
                if(bytes.size())
                {
                    if(send_packet_data(bytes))
                    {
                       f.remove();
                    }
                 }
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

    send_image_data();
    send_map_markup_data();
    send_text_data();
    send_voice_data();

}


////////////////////
void writer_work_thread::process_data_packet(const text_data_packet& )
{

}

void writer_work_thread::process_data_packet(const voice_data_packet& )
{

}

void writer_work_thread::process_data_packet(const markup_data_packet& )
{

}

