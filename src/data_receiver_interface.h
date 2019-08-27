#ifndef DATA_RECEIVER_INTERFACE_H
#define DATA_RECEIVER_INTERFACE_H

#include <QString>
#include <QObject>

class data_receiver_interface : public QObject
{
    Q_OBJECT
public:
    data_receiver_interface(QObject* p) : QObject(p) { }
    virtual ~data_receiver_interface() {}

signals:
    void incoming_connection(QString);
    void connection_status_updates(QString);
    void verification_reply_sent(QString);
    void received_data_status(QString);

public slots:
    virtual void on_recv_error(QString) = 0;

};

#endif // DATA_RECEIVER_INTERFACE_H
