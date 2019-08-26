#ifndef VERIFICATION_DATA_PACKET_H
#define VERIFICATION_DATA_PACKET_H

#include <QByteArray>

class map_markup_verification_data_packet
{
public:
    map_markup_verification_data_packet();
    virtual ~map_markup_verification_data_packet() { }

    void set_identifier(QByteArray& id);

private:
    QByteArray identifier;

};

#endif // VERIFICATION_DATA_PACKET_H
