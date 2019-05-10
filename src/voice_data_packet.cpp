
#include <QByteArray>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QDataStream>

#include "Decoder.h"
#include "voice_data_packet.h"


voice_data_packet::voice_data_packet(QByteArray& bytes)
{
    QDataStream stream(bytes);
    Decoder decoder(stream);
    bytes = decoder.OutputBuffer();

    filename = QString("./incoming_voice_data/voice_data_") +
               QDateTime::currentDateTime().
               toString() +
               QString(".voc");
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
