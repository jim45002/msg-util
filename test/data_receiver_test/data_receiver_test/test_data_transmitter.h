#ifndef TEST_DATA_TRANSMITTER_H
#define TEST_DATA_TRANSMITTER_H

#include <memory>

#include <QObject>

class QNetworkProxy;
class QTcpSocket;

class test_data_transmitter : public QObject
{
    Q_OBJECT
public:
    explicit test_data_transmitter(QObject *parent = nullptr);

    QByteArray make_data_packet();
signals:

public slots:


private:
    std::shared_ptr<QTcpSocket> tcp_socket;
    QNetworkProxy* network_proxy;
};

#endif // TEST_DATA_TRANSMITTER_H
