#ifndef SEND_ERROR_VOICE_DATA_PACKET_H
#define SEND_ERROR_VOICE_DATA_PACKET_H

#include <QByteArray>

class send_error_voice_data_packet
{
public:
    send_error_voice_data_packet(QByteArray id);
    virtual ~send_error_voice_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;
};

#endif // SEND_ERROR_DATA_PACKET_H
