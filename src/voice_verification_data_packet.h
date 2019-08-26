#ifndef VERIFICATION_DATA_PACKET_H
#define VERIFICATION_DATA_PACKET_H

#include <QByteArray>

class voice_verification_data_packet
{
public:
    voice_verification_data_packet();
    virtual ~voice_verification_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;

};

#endif // VERIFICATION_DATA_PACKET_H
