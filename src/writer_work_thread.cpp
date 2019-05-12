
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

void writer_work_thread::run()
{
    ready_write();
    //socket->close();
    //delete socket;
    socket = nullptr;
}

QByteArray writer_work_thread::make_data_packet(const QByteArray b,
                                                packet_type t)
{
    QByteArray packet;
    switch(t)
    {
    case packet_type::t_voice:
    {
        packet_type packet_type = t;
        int packet_size = b.size();       
        packet.append(reinterpret_cast<char*>(&packet_type),
                      sizeof(packet_type));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.toStdString().c_str(),packet_size);
    }
        break;
    case packet_type::t_text:
    {
        packet_type packet_type = t;
        int packet_size = b.size();                
        packet.append(reinterpret_cast<char*>(&packet_type),
                      sizeof(packet_type));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.toStdString().c_str(),packet_size);
    }
        break;
    case packet_type::t_markup:
    {
        packet_type packet_type = t;
        int packet_size = b.size();
        packet.append(reinterpret_cast<char*>(&packet_type),
                      sizeof(packet_type));
        packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
        packet.append(b.toStdString().c_str(),packet_size);
    }
        break;
    }
    return packet;
}

//////////////////////
void writer_work_thread::ready_write()
{

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
                    socket->write(bytes);
                    if(socket->waitForBytesWritten(30000))
                    {
                        qDebug() << "bytes written ";
                    }
                    else
                    {
                        qDebug() << "socket error";
                    }
                    f.remove();
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
                    socket->write(bytes);
                    if(socket->waitForBytesWritten(30000))
                    {
                        qDebug() << "bytes written ";
                    }
                    else
                    {
                        qDebug() << "socket error";
                    }
                    f.remove();
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
                    socket->write(bytes);
                    if(socket->waitForBytesWritten(30000))
                    {
                        qDebug() << "bytes written ";
                    }
                    else
                    {
                        qDebug() << "socket error";
                    }
                    f.remove();
                }
            }
            else
            {
                qDebug() << "unable to open file " << f.fileName();
            }
        }
    };

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

