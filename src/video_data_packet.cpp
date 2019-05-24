
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QString>
#include <QDebug>

#include "video_data_packet.h"

video_data_packet::video_data_packet(QByteArray& bytes, int id)
{
    identifier = QString::number(id);

    filename = QString("./incoming_video_data/video_data_") +
               QDateTime::currentDateTime().
               toString() +
               (".")+identifier +
               QString(".vid.bz2");
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
