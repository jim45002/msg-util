
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QtDebug>

#include "markup_data_packet.h"

markup_data_packet::markup_data_packet(QByteArray& bytes)
{
    filename = QString("markup_data_") +
            QDateTime::currentDateTime().toString() + QString(".dat");
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
