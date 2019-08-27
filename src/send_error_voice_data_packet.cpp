#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "send_error_voice_data_packet.h"

send_error_voice_data_packet::send_error_voice_data_packet(QByteArray)
{

}

void send_error_voice_data_packet::set_identifier(QByteArray &id)
{
    identifier = id;
    QString filename = QString("./send_error_text_data/") + QString(identifier) + ".id";
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
