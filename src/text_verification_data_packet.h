#ifndef VERIFICATION_DATA_PACKET_H
#define VERIFICATION_DATA_PACKET_H

#include <QByteArray>

class text_verification_data_packet
{
public:
    text_verification_data_packet();
    virtual ~text_verification_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;

};

#endif // VERIFICATION_DATA_PACKET_H
