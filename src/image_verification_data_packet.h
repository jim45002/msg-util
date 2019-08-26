#ifndef VERIFICATION_DATA_PACKET_H
#define VERIFICATION_DATA_PACKET_H

#include <QByteArray>

class image_verification_data_packet
{
public:
    image_verification_data_packet();
    virtual ~image_verification_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;

};

#endif // VERIFICATION_DATA_PACKET_H
