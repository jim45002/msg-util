#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "send_error_map_markup_data_packet.h"

send_map_markup_error_data_packet::send_map_markup_error_data_packet()
{

}

void send_map_markup_error_data_packet::set_identifier(QByteArray &id)
{
    identifier = id;
    QString filename = QString("./send_error_map_markup_data/") + QString(identifier) + ".id";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        if(file.write(identifier) == identifier.size())
        {

        }
        else
        {
            qDebug() << "file write error on " << file.fileName();
        }
    }
    else
    {
        qDebug() << "unable to open file " << file.fileName();
    }
}
