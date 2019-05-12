
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QtDebug>

#include "markup_data_packet.h"

markup_data_packet::markup_data_packet(QByteArray& bytes)
{
    filename = QString("./incoming_map_markup_data/markup_data_") +
            QDateTime::currentDateTime().toString() + QString(".bz2");
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
