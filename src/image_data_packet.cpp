
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QtDebug>

#include "image_data_packet.h"

image_data_packet::image_data_packet(QByteArray& bytes)
{
    filename = QString("./incoming_image_data/image_data_") +
            QDateTime::currentDateTime().toString().remove(' ') + QString(".bz2");
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        if(file.write(bytes) == bytes.size())
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
