#ifndef VOICE_DATA_PACKET_H
#define VOICE_DATA_PACKET_H

#include <QString>

class QByteArray;

class voice_data_packet
{
public:
    voice_data_packet(QByteArray&, int id=0);

private:
    QString filename;
    QString identifier;
};

#endif // VOICE_DATA_PACKET_H
