#ifndef SEND_ERROR_DATA_PACKET_H
#define SEND_ERROR_DATA_PACKET_H

#include <QByteArray>

class send_error_image_data_packet
{
public:
    send_error_image_data_packet();
    virtual ~send_error_image_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;
};

#endif // SEND_ERROR_DATA_PACKET_H
