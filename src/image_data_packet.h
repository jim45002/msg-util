#ifndef IMAGE_DATA_PACKET_H
#define IMAGE_DATA_PACKET_H

#include <QString>

class QByteArray;

class image_data_packet
{
public:
    image_data_packet(QByteArray&);

private:
    QString filename;
};
#endif // IMAGE_DATA_PACKET_H
