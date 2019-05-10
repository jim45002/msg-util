#ifndef MARKUP_DATA_PACKET_H
#define MARKUP_DATA_PACKET_H

#include <QString>

class QByteArray;

class markup_data_packet
{
public:
    markup_data_packet(QByteArray&);

private:
    QString filename;
};

#endif // MARKUP_DATA_PACKET_H
