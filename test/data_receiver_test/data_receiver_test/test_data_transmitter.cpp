#include <thread>
#include <chrono>

#include <QBitArray>
#include <QTcpSocket>
#include <QNetworkProxy>

#include "test_data_transmitter.h"

test_data_transmitter::test_data_transmitter(QObject *parent) : QObject(parent)
{
    network_proxy = new QNetworkProxy(QNetworkProxy::Socks5Proxy,
                                      QString("127.0.0.1"),
                                      9052);
    tcp_socket = std::make_shared<QTcpSocket>();
    tcp_socket->setProxy(*network_proxy);

    qDebug() << "connecting to host";
    tcp_socket->connectToHost(QString("uuydgvo3fkxlwjfjbibdyao"
                                      "favnvfqhlza5njju2d5fzqn"
                                      "gx2bhildad.onion"),80);
    tcp_socket->waitForConnected(60000);

    QByteArray b = make_data_packet();

    tcp_socket->write(b);
    if(tcp_socket->waitForBytesWritten(60000))
    {
        qDebug() << "bytes written ";
    }
    else
    {
        qDebug() << "socket error";
    }
}

QByteArray test_data_transmitter::make_data_packet()
{
    int packet_type = 16;
    int packet_size = 3000;
    char packet_data[3000];

    QByteArray packet;
    packet.append(reinterpret_cast<char*>(&packet_type),sizeof(int));
    packet.append(reinterpret_cast<char*>(&packet_size),sizeof (int));
    packet.append(packet_data,packet_size);

    return packet;
}
