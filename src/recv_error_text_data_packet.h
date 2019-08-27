#ifndef RECV_ERROR_TEXT_DATA_PACKET_H
#define RECV_ERROR_TEXT_DATA_PACKET_H

#include <QByteArray>

class recv_error_text_data_packet
{
public:
    recv_error_text_data_packet(QByteArray &data);
    virtual ~recv_error_text_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;

};

#endif // RECV_ERROR_DATA_PACKET_H
