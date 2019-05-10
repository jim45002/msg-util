#ifndef TEXT_DATA_PACKET_H
#define TEXT_DATA_PACKET_H

#include <QStringList>

class QByteArray;

class text_data_packet
{
public:
    text_data_packet(QByteArray&);

private:
    QString filename;
};

#endif // TEXT_DATA_PACKET_H
