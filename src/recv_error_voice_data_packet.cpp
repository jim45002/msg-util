#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "recv_error_data_packet.h"

recv_error_data_packet::recv_error_data_packet()
{

}

void recv_error_data_packet::set_identifier(QByteArray &id)
{
    identifier = id;
    QString filename = QString("./recv_error_text_data/") + QString(identifier) + ".id";
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
