#ifndef VIDEO_DATA_PACKET_H
#define VIDEO_DATA_PACKET_H

#include <QString>

class video_data_packet
{
public:
    video_data_packet(QByteArray& bytes, int id);

private:
    QString filename;
    QString identifier;
};

#endif // VIDEO_DATA_PACKET_H
